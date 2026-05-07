void WhichTagged()
{
    if (ptrRfidMain != nullptr) ptrRfidMain();
    if (ptrRfidSub  != nullptr) ptrRfidSub();
}

void DoorOpen(){
    digitalWrite(RELAY_PIN, LOW);
    if(strCurState == "debuff"){  //debuff 인경우위해서?
        DebugSerial.println("DEBUFF OPEN");
    }
    else{
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "activate");
        RoundNeoEffectDown(BLACK);
        has2wifi.Loop(DataChanged); //LOCK -> ACTIVATE 바뀐것을 업데이트 받기 위함
        AllNeoOn(YELLOW);
    }
    digitalWrite(RELAY_PIN, LOW);
}

void GhostDoorOpen(){
    digitalWrite(RELAY_PIN, LOW);
    RoundNeoEffectDown(BLACK);
    // delay(3000);
}

// ======================== NEWBIE MODE ========================

void NewbiePlayerOpen() {
    ReturnNormalState();
    ptrRfidMode = NewbieLogin;
    Mp3PlayLargeFolder(1, VD1);
    digitalWrite(RELAY_PIN, HIGH);
    has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
    RoundNeoEffect(GREEN);
    GhostDoorOpen();
    has2wifi.Send((String)(const char*)my["device_name"], "device_state", "lock");
    AllNeoOn(GREEN);
    SubSerialFlush();
    MainSerialFlush();
    delay(1000);
    has2wifi.Loop(DataChanged);
}

void NewbieGhostOpen() {
    ReturnNormalState();
    ptrRfidMode = NewbieLogin;
    Mp3PlayLargeFolder(1, VD1);
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
}

void NewbieLogin(char role) {
    Login(role);
}

void NewbiePlayerUnlockTimerFunc() {
    gameTimerCnt++;
    RoundNeoToggle(GREEN, gameTimerCnt);
    LineNeoDown(YELLOW, GREEN, map(gameTimerCnt, 0, playerUnlockTime, 0, NumPixels[LINE]));
    if (gameTimerCnt == 1)
        Mp3PlayLargeFolder(1, VD11);
    if (gameTimerCnt > playerUnlockTime) {
        has2wifi.ReceiveMine();
        DataChanged();
        if (strCurState != "lock") {
            DebugSerial.println("debuff on");
            CancelTagProgress();
        } else {
            DebugSerial.println("DOOR UNLOCK (Newbie Player)!");
            Mp3PlayLargeFolder(1, VD7);
            NewbiePlayerOpen();
        }
    }
}

void NewbieGhostUnlockTimerFunc() {
    gameTimerCnt++;
    RoundNeoUp(BLUE, GREEN, map(gameTimerCnt, 0, ghostOpenTime, 0, NumPixels[ROUND] / 2));
    if (gameTimerCnt > ghostOpenTime) {
        has2wifi.ReceiveMine();
        DataChanged();
        if (strCurState != "lock") {
            DebugSerial.println("debuff on");
            CancelTagProgress();
        } else {
            DebugSerial.println("GHOST OPEN (Newbie)!");
            Mp3PlayLargeFolder(1, VD1);
            NewbieGhostOpen();
        }
    }
}