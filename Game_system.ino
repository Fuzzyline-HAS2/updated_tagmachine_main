void WhichTagged()
{
    ptrRfidMain();
    ptrRfidSub();
}

void DoorOpen(){
    digitalWrite(RELAY_PIN, LOW);
    RoundNeoEffectDown(BLACK);
    has2wifi.Send((String)(const char*)my["device_name"], "device_state", "activate");
    AllNeoOn(YELLOW);
}

void GhostDoorOpen(){
    digitalWrite(RELAY_PIN, LOW);
    RoundNeoEffectDown(BLACK);
    // delay(3000);
}