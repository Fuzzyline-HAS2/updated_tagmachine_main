void WhichTagged()
{
    ptrRfidMain();
    ptrRfidSub();
}

void DoorOpen(){
    digitalWrite(RELAY_PIN, LOW);
    if(strCurState == "debuff"){  //debuff 인경우위해서?
        Serial.println("DEBUFF OPEN");
    }
    else if(strMode == "easy"){  // 뉴비모드: 문 열린 후 즉시 lock 복귀
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
        has2wifi.Loop(DataChanged); // open 서버 등록 대기
        RoundNeoEffectDown(BLACK);  // open 상태가 3초간 서버에 표시됨
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "lock");
        has2wifi.Loop(DataChanged);
        AllNeoOn(GREEN);
    }
    else{
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
        has2wifi.Loop(DataChanged); // open 서버 등록 대기
        RoundNeoEffectDown(BLACK);  // open 상태가 3초간 서버에 표시됨
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "activate");
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