void CheckingPlayers(String tagUser) //어떤 카드가 들어왔는지 확인용
{ 
  Serial.println("tag_user_data : " + tagUser);     // 1. 태그한 플레이어의 역할과 생명칩갯수, 최대생명칩갯수 등 읽어오기
  if(tagUser == "MMMM"){  //스태프카드 
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
    digitalWrite(RELAY_PIN, LOW);
  }
  else{
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
      if(strLastTagUser == tagUser){  //Login 진행한 태그와 같은지 확인
        Serial.println("LoginRole: " + String(loginRole));
        ptrRfidMode(loginRole);
      }
      else{
        Serial.println("Different TAG deteced");
        ptrRfidFail();
      }
    }
    strLastTagUser = tagUser;
  }
  
}

void Login(char role)
{ 
  Serial.println("LOGIN");
  loginDone = true;
  lightColor(pixels[ROUND], color[BLACK]);
  lightColor(pixels[ROUND_SUB], color[BLACK]);

  GameTimer.deleteTimer(gameTimerId);
  gameTimerId = GameTimer.setInterval(1000,GameTimerFunc);
  WifiTimer.deleteTimer(wifiTimerId); 
  gameTimerCnt = 0;
  if(mainRfidTagged == true)
  {
    ptrRfidMain = CommnunicationMainBeetle;
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
      if(playerUnlockTime == 0){
        GameTimer.deleteTimer(gameTimerId);
        Mp3PlayLargeFolder(1, VD7);
        Serial.println("DOOR UNLOCK! (instant)");
        ReturnNormalState();
        digitalWrite(RELAY_PIN, HIGH);
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
        RoundNeoEffect(GREEN);
        DoorOpen();
        SubSerialFlush();
        MainSerialFlush();
      } else {
        ptrGameTimer = PlayerUnlockTimerFunc;
        ptrRfidFail = UnlockFail;
        ptrRfidMode = WaitRfid;
      }
    }
    else if(role == 'G')
    {
      if(ghostOpenTime == 0){
        GameTimer.deleteTimer(gameTimerId);
        Mp3PlayLargeFolder(1, VD1);
        Serial.println("GHOST OPEN (instant)");
        ReturnNormalState();
        digitalWrite(RELAY_PIN, HIGH);
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
        RoundNeoEffect(BLUE);
        GhostDoorOpen();
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "lock");
        AllNeoOn(GREEN);
        SubSerialFlush();
        MainSerialFlush();
        delay(1000);
        has2wifi.Loop(DataChanged);
      } else {
        ptrGameTimer = GhostUnlockTimerFunc;
        ptrRfidFail = GhostOpenFailLock;
        ptrRfidMode = WaitRfid;
      }
    }
    else if(role == 'T')
    {
      if(taggerUnlockTime == 0){
        Mp3PlayLargeFolder(1, VD1);
        Serial.println("Tagger Door Open (instant)");
        digitalWrite(RELAY_PIN, HIGH);
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
        RoundNeoEffect(PURPLE);
        AllNeoOn(PURPLE);
        DoorOpen();
        ReturnNormalState();
      } else {
        ptrGameTimer = TaggerUnlockTimerFunc;
        ptrRfidFail = UnlockFail;
        ptrRfidMode = WaitRfid;
      }
    }
  }
  else if((String)(const char*)my["device_state"] == "debuff")
  {
    AllNeoOn(PURPLE);
    if(role == 'P')
    {
      NeoBlink(ROUND,RED,2,400);
      AllNeoOn(PURPLE);
      ReturnNormalState();
    }
    else if(role == 'G')
    {
      NeoBlink(ROUND,RED,2,400);
      AllNeoOn(PURPLE);
      ReturnNormalState();
    }
    else if(role == 'T')
    {
      Mp3PlayLargeFolder(1, VD1);
      Serial.println("Tagger Door Open");
      digitalWrite(RELAY_PIN, HIGH);

      RoundNeoEffect(PURPLE);
      AllNeoOn(PURPLE);
      RoundNeoEffectDown(BLACK);
      DoorOpen();
      ReturnNormalState();                                                       //시리얼 통신 버퍼 flush
      AllNeoOn(PURPLE);
    }
  }
  else  //도어 UNLOCK 일때
  {
    if(role == 'P')
    {
      if(playerLockTime == 0){
        GameTimer.deleteTimer(gameTimerId);
        has2wifi.ReceiveMine();
        DataChanged();
        if(strCurState != "activate"){
          Serial.println("debuff on");
          loginDone = false;
        } else {
          Serial.println("DOOR LOCK! (instant)");
          has2wifi.Send((String)(const char*)my["device_name"], "device_state", "lock");
          Mp3PlayLargeFolder(1, VD4);
          ReturnNormalState();
          RoundNeoEffect(GREEN);
          SubSerialFlush();
          MainSerialFlush();
        }
      } else {
        Serial.println("LoginTimerSelector PlayerSelected");
        ptrGameTimer = PlayerLockTimerFunc;
        ptrRfidFail = LockFail;
        ptrRfidMode = WaitRfid;
      }
    }
    else if(role == 'G')
    {
      if(ghostOpenTime == 0){
        GameTimer.deleteTimer(gameTimerId);
        Mp3PlayLargeFolder(1, VD1);
        Serial.println("GHOST OPEN (instant)");
        ReturnNormalState();
        digitalWrite(RELAY_PIN, HIGH);
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
        RoundNeoEffect(BLUE);
        GhostDoorOpen();
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "activate");
        AllNeoOn(YELLOW);
        SubSerialFlush();
        MainSerialFlush();
        delay(1000);
        has2wifi.Loop(DataChanged);
      } else {
        ptrGameTimer = GhostLockTimerFunc;
        ptrRfidFail = GhostOpenFailUnlock;
        ptrRfidMode = WaitRfid;
      }
    }
    else if(role == 'T')
    {
      Mp3PlayLargeFolder(1, VD1);
      Serial.println("Tagger Door Open");
      digitalWrite(RELAY_PIN, HIGH);
      has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
      RoundNeoEffect(PURPLE);
      DoorOpen();
      ReturnNormalState();
    }
  }
}
void LockFail()
{ 
  has2wifi.ReceiveMine();
  DataChanged();
  // Serial.println("strCurState:" + String(strCurState));
  if(strCurState != "activate"){
      Serial.println("debuff on");
      loginDone = false;
  }
  else{
    Mp3PlayLargeFolder(1, VD1);
    Serial.println("Lock Fail Door Open");
    digitalWrite(RELAY_PIN, HIGH);
    has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
    RoundNeoEffect(YELLOW);
    AllNeoOn(YELLOW);
    DoorOpen();
    ReturnNormalState();
  }
}
void UnlockFail()
{ 
  has2wifi.ReceiveMine();
  DataChanged();
  // Serial.println("strCurState:" + String(strCurState));
  if(strCurState != "lock"){
      Serial.println("debuff on");
      loginDone = false;
  }
  else{
    Mp3PlayLargeFolder(1, VD6);
    Serial.println("Unlock Fail Door Shut");
    NeoBlink(ROUND,RED,5,500);
    AllNeoOn(GREEN);
    ReturnNormalState();
  }
}

void GhostOpenFailUnlock()
{ 
  // has2wifi.ReceiveMine();
  // DataChanged();
  // // Serial.println("strCurState:" + String(strCurState));
  // if(strCurState != "lock"){
  //     Serial.println("debuff on");
  // }
  // else{
  Mp3PlayLargeFolder(1, VD6);
  Serial.println("Ghost Door OpenFail");
  NeoBlink(ROUND,RED,5,500);
  AllNeoOn(YELLOW);
  ReturnNormalState();
  // // }
}
void GhostOpenFailLock()
{ 
  // has2wifi.ReceiveMine();
  // DataChanged();
  // // Serial.println("strCurState:" + String(strCurState));
  // if(strCurState != "activate"){
  //     Serial.println("debuff on");
  // }
  // else{
  Mp3PlayLargeFolder(1, VD6);
  Serial.println("Unlock Fail Door Shut");
  NeoBlink(ROUND,RED,5,500);
  AllNeoOn(GREEN);
  ReturnNormalState();
  // }
}
