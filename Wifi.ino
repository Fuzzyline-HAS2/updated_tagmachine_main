void DataChanged()
{
  static StaticJsonDocument<500> cur;   //저장되어 있는 cur과 읽어온 my 값과 비교후 실행
  if((String)(const char*)my["game_state"] != (String)(const char*)cur["game_state"]){  
    if((String)(const char*)my["game_state"] == "setting"){
        strCurState = "setting";
        SettingFunc();
    }
    else if((String)(const char*)my["game_state"] == "ready"){
        strCurState = "ready";
        ReadyFunc();
    }
    else if((String)(const char*)my["game_state"] == "activate"){
        strCurState = "activate";
        ActivateFunc();
    }
  }
  if((String)(const char*)my["device_state"] != (String)(const char*)cur["device_state"]){  
    if((String)(const char*)my["device_state"] == "lock"){ 
      strCurState = "lock";
      AllNeoOn(GREEN);
    }
    else if((String)(const char*)my["device_state"] == "mo"){ 
        digitalWrite(RELAY_PIN, HIGH);
        delay(1000);
        digitalWrite(RELAY_PIN, LOW);
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", (String)(const char*)cur["device_state"]);
    }
    else if((String)(const char*)my["device_state"] == "activate"){
        strCurState = "activate";
        ActivateFunc();
    }
  }
  if((String)(const char*)my["device_state"] == "debuff"){ 
    strCurState = "debuff";
    ptrRfidFail = WaitFunc;
    AllNeoOn(PURPLE);
    Serial.println("디버프 시작");
    DebuffTimer.deleteTimer(debuffTimerId);
    debuffTimerId = DebuffTimer.setInterval(60000,DebuffTimerFunc);
    ReturnNormalState();
  }
  cur = my; // cur 데이터 그룹에 현재 읽어온 데이터 저장
}
void WaitFunc(){

}
void SettingFunc(void){
    Serial.println("SETTING");
    DebuffTimer.deleteTimer(debuffTimerId);
    SubSerialTimer.deleteTimer(subSerialTimerId);
    GameTimer.deleteTimer(gameTimerId);
    WifiTimer.deleteTimer(wifiTimerId);                                          //게임 타이머 종료
    wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);
    
    AllNeoOn(WHITE);
    digitalWrite(RELAY_PIN, HIGH);
    ptrCurrentMode = WaitFunc;
    ptrRfidMode = WaitRfid;

}
void ActivateFunc(void){
    Serial.println("ACTIVATE");
    DebuffTimer.deleteTimer(debuffTimerId);
    SubSerialTimer.deleteTimer(subSerialTimerId);
    GameTimer.deleteTimer(gameTimerId);
    WifiTimer.deleteTimer(wifiTimerId);                                          //게임 타이머 종료
    wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);

    AllNeoOn(YELLOW);
    digitalWrite(RELAY_PIN, LOW);
    ptrCurrentMode = WhichTagged;
    ptrRfidMode = Login;
    ptrRfidFail = WaitFunc;
    ptrRfidMain = RfidLoopMain;
    ptrRfidSub = CommnunicationBeetle;
}
void ReadyFunc(void){
    Serial.println("READY");
    DebuffTimer.deleteTimer(debuffTimerId);
    SubSerialTimer.deleteTimer(subSerialTimerId);
    GameTimer.deleteTimer(gameTimerId);
    WifiTimer.deleteTimer(wifiTimerId);                                          //게임 타이머 종료
    wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);

    AllNeoOn(RED);
    digitalWrite(RELAY_PIN, HIGH);
    ptrCurrentMode = WaitFunc;
    ptrRfidMode = WaitRfid;
}
void GameSetting(){
    playerLockTime = (int)my["player_lock_time"];
    playerUnlockTime = (int)my["player_unlock_time"];
    taggerUnlockTime = (int)my["tagger_unlock_time"];
    ghostOpenTime = (int)my["ghost_open_time"];
}