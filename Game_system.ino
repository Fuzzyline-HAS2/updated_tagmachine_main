void WhichTagged()
{
    ptrRfidMain();
    ptrRfidSub();
}

void DoorOpen(){
    delay(100);
    has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
    delay(1000);
    digitalWrite(RELAY_PIN, LOW);
    delay(3000);
    has2wifi.Send((String)(const char*)my["device_name"], "device_state", "activate");
    AllNeoOn(YELLOW);
    delay(1000);
}

void GhostDoorOpen(){
    delay(100);
    has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
    delay(1000);
    digitalWrite(RELAY_PIN, LOW);
    delay(3000);
}