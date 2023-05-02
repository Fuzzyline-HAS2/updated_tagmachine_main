 ;/**
 * @file Done_ItemBox_code.ino
 * @author 김병준 (you@domain.com)
 * @brief
 * @version 1.0
 * @date 2022-11-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "tagmachine_main.h"

void setup() {
    Serial.begin(115200);
    toSubSerial.begin(9600, SERIAL_8N1, BEETLE_RX_PIN, BEETLE_TX_PIN);
//    has2wifi.Setup("city");
     has2wifi.Setup("badland");
    // has2wifi.Setup("KT_GiGA_6C64","ed46zx1198");
    // has2wifi.Setup();
    NeopixelInit();
    RfidInit();
    TimerInit();
    Mp3_Setup();
    pinMode(RELAY_PIN, OUTPUT);
    GameSetting();
    DataChanged();
}
void loop() {
    ptrCurrentMode();
    WifiTimer.run();
    GameTimer.run();
    SubSerialTimer.run();
}
