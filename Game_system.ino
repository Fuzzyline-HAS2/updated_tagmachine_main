void WhichTagged()
{
    ptrRfidMain();
    ptrRfidSub();
}

void DoorOpen(){
    digitalWrite(RELAY_PIN, LOW);
    has2wifi.Send((String)(const char*)my["device_name"], "device_state", "activate");
    RoundNeoEffectDown(BLACK);
    has2wifi.Loop(DataChanged); //LOCK -> ACTIVATE 바뀐것을 업데이트 받기 위함
    AllNeoOn(YELLOW);
}

void GhostDoorOpen(){
    digitalWrite(RELAY_PIN, LOW);
    RoundNeoEffectDown(BLACK);
    // delay(3000);
}