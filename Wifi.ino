void DataChanged()
{
  static StaticJsonDocument<1000> cur;  //저장되어 있는 cur과 읽어온 my 값과 비교후 실행
  if (my["brightness"].as<int>() != cur["brightness"].as<int>()) {
    UpdateBrightness();
  }
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
    String deviceState = (String)(const char*)my["device_state"];
    if(deviceState == "lock"){
      strCurState = deviceState;
      if(loginDone) QueuePendingDeviceState(deviceState);
      else ApplyDeviceState(deviceState);
    }
    else if(deviceState == "mo"){
        digitalWrite(RELAY_PIN, HIGH);
        delay(1000);
        digitalWrite(RELAY_PIN, LOW);
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", (String)(const char*)cur["device_state"]);
    }
    else if(deviceState == "activate"){
        strCurState = deviceState;
        if(loginDone) QueuePendingDeviceState(deviceState);
        else ApplyDeviceState(deviceState);
    }
    else if(deviceState == "github"){
        ota.check();
    }
    else if(deviceState == "tagger"){
        ApplyDeviceState("tagger");
    }
  }
  if((String)(const char*)my["device_state"] == "debuff"){ 
    ApplyDeviceState("debuff");
  }
  GameSetting();
  NewbieModeSetting();
  {
    String _ds = (String)(const char*)my["device_state"];
    if (_ds == "lock" || _ds == "activate" || _ds == "debuff") strCurState = _ds;
  }
  cur = my; // cur 데이터 그룹에 현재 읽어온 데이터 저장
}

void QueuePendingDeviceState(String deviceState) {
    pendingDeviceState = deviceState;
    pendingDeviceStateApply = true;
    Serial.println("Queue Device State: " + deviceState);
}

void ApplyPendingDeviceState() {
    if (!pendingDeviceStateApply || loginDone) return;

    String deviceState = pendingDeviceState;
    pendingDeviceState = "";
    pendingDeviceStateApply = false;
    ApplyDeviceState(deviceState);
}

void ApplyDeviceState(String deviceState) {
    if(deviceState == "lock"){
      strCurState = "lock";
      AllNeoOn(GREEN);
      digitalWrite(RELAY_PIN, LOW);            // 도어 잠금(닫힘) - tagger 등 오픈 상태에서 복귀 시 보장
    }
    else if(deviceState == "activate"){
        strCurState = "activate";
        ActivateFunc();
    }
    else if(deviceState == "debuff"){
        pendingDeviceState = "";
        pendingDeviceStateApply = false;
        strCurState = "debuff";
        ptrRfidFail = WaitFunc;
        AllNeoOn(PURPLE);
        digitalWrite(RELAY_PIN, LOW);            // 디버프 대기 중 도어 잠금(닫힘)
        Serial.println("디버프 시작");
        DebuffTimer.deleteTimer(debuffTimerId);
        debuffTimerId = DebuffTimer.setInterval(60000,DebuffTimerFunc);
        ReturnNormalState();
    }
    else if(deviceState == "tagger"){
        pendingDeviceState = "";
        pendingDeviceStateApply = false;
        strCurState = "tagger";
        AllNeoOn(PURPLE);                       // 전체 보라색
        digitalWrite(RELAY_PIN, HIGH);          // 도어 오픈, 계속 유지
        WifiTimer.deleteTimer(wifiTimerId);
        wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);
        ptrCurrentMode = WhichTagged;           // 태그 읽기 활성화(상태와 무관하게 보장)
        ptrRfidMain   = CommnunicationMainBeetle;
        ptrRfidSub    = CommnunicationBeetle;
        ptrRfidMode   = Login;
        ptrRfidFail   = WaitFunc;
    }
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
    GameSetting();
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
    ptrRfidMain = CommnunicationMainBeetle;
    ptrRfidSub = CommnunicationBeetle;
    GameSetting();
    NewbieModeSetting();
    if ((String)(const char*)my["mode"] == "easy") {
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "lock");
        my["device_state"] = "lock";
        strCurState = "lock";
        AllNeoOn(GREEN);
    }
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
    GameSetting();
}
void GameSetting(){
    playerLockTime = (int)my["player_lock_time"];
    playerUnlockTime = (int)my["player_unlock_time"];
    taggerUnlockTime = (int)my["tagger_unlock_time"];
    ghostOpenTime = (int)my["ghost_open_time"];
}
void NewbieModeSetting() {
    if ((String)(const char*)my["mode"] == "easy" &&
        (String)(const char*)my["game_state"] == "activate" &&
        (String)(const char*)my["device_state"] != "tagger") {
        ptrRfidMode = NewbieLogin;
    }
}
