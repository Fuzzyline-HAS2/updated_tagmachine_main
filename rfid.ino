void RfidInit()
{
  RestartPn532:
  nfc.begin();
  if (!(nfc.getFirmwareVersion()))
  {
    Serial.print("PN532 연결실패");
    AllNeoOn(RED);
    goto RestartPn532;
  }
  else
  {
    nfc.SAMConfig();
    Serial.print("PN532 연결성공");
    rfid_init_complete = true;
    AllNeoOn(YELLOW);
  }
  delay(100);
}

void RfidLoopMain()
{
  uint8_t uid[3][7] = {{0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0}}; // Buffer to store the returned UID
  uint8_t uidLength[] = {0};                   // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t data[32];
  byte pn532_packetbuffer11[64];
  pn532_packetbuffer11[0] = 0x00;
  mainRfidTagged = true;
  if (nfc.sendCommandCheckAck(pn532_packetbuffer11, 1)){ // rfid 통신 가능한 상태인지 확인
    if (nfc.startPassiveTargetIDDetection(PN532_MIFARE_ISO14443A)){                                       // rfid에 tag 찍혔는지 확인용 //데이터 들어오면 uid정보 가져오기
      if (nfc.ntag2xx_ReadPage(7, data)){ // ntag 데이터에 접근해서 불러와서 data행열에 저장
        Serial.println("TAGGGED");
        String tagUser = "";
        for(int i = 0; i < 4; i++)    //GxPx 데이터만 배열에서 추출해서 string으로 저장
          tagUser += (char)data[i];

        CheckingPlayers(tagUser);

      }
    }
    else
    {
      ptrRfidFail();
    }
  }
}

void CheckingPlayers(String tagUser) //어떤 카드가 들어왔는지 확인용
{ 
  Serial.println("tag_user_data : " + tagUser);     // 1. 태그한 플레이어의 역할과 생명칩갯수, 최대생명칩갯수 등 읽어오기
  if(tagUser == "MMMM"){  //스태프카드 초기화
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
    digitalWrite(RELAY_PIN, LOW);
  }
  if(loginDone == false)                            // 로그인할때만 체크함
  {
    has2wifi.Receive(tagUser);                      // 2. 술래인지, 플레이어인지 구분
    if((String)(const char*)tag["role"] == "player"){ // 3. 태그한 사용자가 플레이어고
      Serial.println("Player Tagged");
      loginRole = 'P';
      ptrRfidMode('P');
    }
    else if((String)(const char*)tag["role"] == "tagger"){ // 3. 태그한 사용자가 플레이어고
      Serial.println("Tagger Tagged");
      loginRole = 'T';
      ptrRfidMode('T');
    }
    else if((String)(const char*)tag["role"] == "ghost" || (String)(const char*)tag["role"] == "revival"){ // 3. 태그한 
      Serial.println("Ghost Tagged");
      loginRole = 'G';
      ptrRfidMode('G');
    }
    else{ 
      Serial.println("Wrong TAG");
    }
  }
  else
  {
    Serial.println("LoginRole: " + String(loginRole));
    ptrRfidMode(loginRole);
  }
}

void Login(char role)
{ 
  Serial.println("LOGIN");
  // GameTimer.enable(gameTimerId);        //게임 타이머  
  loginDone = true;
  pixels[ROUND].lightColor(color[BLACK]);
  pixels[ROUND_SUB].lightColor(color[BLACK]);
  
  gameTimerId = GameTimer.setInterval(1000,GameTimerFunc);
  WifiTimer.deleteTimer(wifiTimerId); 
  gameTimerCnt = 0;
  if(mainRfidTagged == true)
  {
    ptrRfidMain = RfidLoopMain;
    ptrRfidSub = WaitFunc;
    LoginTimerSelector(role);
  }
  else if(mainRfidTagged == false)
  {
    ptrRfidMain = WaitFunc;
    ptrRfidSub = CommnunicationBeetle;
    LoginTimerSelector(role);
  }
}

void WaitRfid(char role)
{
  Serial.println("WAIT RFID");
}
void LoginTimerSelector(char role){
  Serial.println("LoginTimerSelector");
  if((String)(const char*)my["device_state"] == "lock")
  {
    if(role == 'P')       
    {
      ptrGameTimer = PlayerUnlockTimerFunc;
      ptrRfidFail = UnlockFail;
      ptrRfidMode = WaitRfid;
    }
    else if(role == 'G')  
    {
      ptrGameTimer = GhostUnlockTimerFunc;
      ptrRfidFail = GhostOpenFailLock;
      ptrRfidMode = WaitRfid;
    }
    else if(role == 'T')  
    {
      ptrGameTimer = TaggerUnlockTimerFunc;
      ptrRfidFail = UnlockFail;
      ptrRfidMode = WaitRfid;
    }
  }
  else
  {
    if(role == 'P')       
    {
      Serial.println("LoginTimerSelector PlayerSelected");
      ptrGameTimer = PlayerLockTimerFunc;
      ptrRfidFail = LockFail;
      ptrRfidMode = WaitRfid;
    }
    else if(role == 'G')  
    {
      ptrGameTimer = GhostLockTimerFunc;
      ptrRfidFail = GhostOpenFailUnlock;
      ptrRfidMode = WaitRfid;
    }
    else if(role == 'T') 
    {
      loginDone = false;
      myDFPlayer.playLargeFolder(1, VD1);
      Serial.println("Tagger Door Open");
      GameTimer.deleteTimer(gameTimerId);        //게임 타이머 정지
      digitalWrite(RELAY_PIN, HIGH);  
      
      RoundNeoEffect(PURPLE);
      
      AllNeoOn(PURPLE);
      DoorOpen();
      AllNeoOn(YELLOW);

      ptrRfidMain = RfidLoopMain;
      ptrRfidSub = CommnunicationBeetle;
      ptrRfidMode = Login;
      ptrRfidFail = WaitFunc;

      wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);
    }
  }
}
void LockFail()
{ 
  loginDone = false;
  myDFPlayer.playLargeFolder(1, VD1);
  Serial.println("Lock Fail Door Open");
  GameTimer.deleteTimer(gameTimerId);        //게임 타이머 정지
  digitalWrite(RELAY_PIN, HIGH);
  RoundNeoEffect(YELLOW);
  AllNeoOn(YELLOW);
  DoorOpen();
  AllNeoOn(YELLOW);
  ptrRfidMain = RfidLoopMain;
  ptrRfidSub = CommnunicationBeetle;
  ptrRfidMode = Login;
  ptrRfidFail = WaitFunc;
  wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);
}
void UnlockFail()
{ 
  loginDone = false;
  myDFPlayer.playLargeFolder(1, VD6);
  Serial.println("Unlock Fail Door Shut");
  GameTimer.deleteTimer(gameTimerId);        //게임 타이머 정지
  NeoBlink(ROUND,RED,5,500);
  AllNeoOn(GREEN);
  ptrRfidMain = RfidLoopMain;
  ptrRfidSub = CommnunicationBeetle;
  ptrRfidMode = Login;
  ptrRfidFail = WaitFunc;
  wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);
}

void GhostOpenFailUnlock()
{ 
  loginDone = false;
  myDFPlayer.playLargeFolder(1, VD6);
  Serial.println("Ghost Door OpenFail");
  GameTimer.deleteTimer(gameTimerId);        //게임 타이머 정지
  NeoBlink(ROUND,RED,5,500);
  AllNeoOn(YELLOW);
  ptrRfidMain = RfidLoopMain;
  ptrRfidSub = CommnunicationBeetle;
  ptrRfidMode = Login;
  ptrRfidFail = WaitFunc;
  wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);
}
void GhostOpenFailLock()
{ 
  loginDone = false;
  myDFPlayer.playLargeFolder(1, VD6);
  Serial.println("Unlock Fail Door Shut");
  GameTimer.deleteTimer(gameTimerId);        //게임 타이머 정지
  NeoBlink(ROUND,RED,5,500);
  AllNeoOn(GREEN);
  ptrRfidMain = RfidLoopMain;
  ptrRfidSub = CommnunicationBeetle;
  ptrRfidMode = Login;
  ptrRfidFail = WaitFunc;
  wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);
}