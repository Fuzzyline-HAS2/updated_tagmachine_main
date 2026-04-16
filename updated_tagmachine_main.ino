/**
 * @file updated_tagmachine_main.ino
 * @author 김병준 (you@domain.com)
 * @brief
 * @version 1.0
 * @date 2022-11-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#define FIRMWARE_VER 7
#include "updated_tagmachine_main.h"

void setup() {
    Serial.begin(115200);
    toSubSerial.begin(9600, SERIAL_8N1, SUB_BEETLE_RX_PIN, SUB_BEETLE_TX_PIN);
    toMainSerial.begin(9600, SERIAL_8N1, MAIN_BEETLE_RX_PIN, MAIN_BEETLE_TX_PIN);
    NeopixelInit();
    TimerInit();
    Mp3_Setup();
    pinMode(RELAY_PIN, OUTPUT);
//  has2wifi.Setup("city");
    has2wifi.Setup("city");
    ota.setLogStream(Serial);
    ota.setOnSuccess([]() {
        NeoBlink(LINE, RED, 5, 300);
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "setting");
    });
    ota.setOnSkip([]() {
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", "setting");
    });
    DataChanged();
    GameSetting();

    // Main Beetle 핸드셰이크 (최대 10초)
    Serial.println("=== Main Beetle Handshake Start ===");
    unsigned long hsStart = millis();
    while(millis() - hsStart < 10000) {
        if(toMainSerial.available() > 0) {
            String cmd = toMainSerial.readStringUntil('\n');
            Serial.println("Main Beetle RX: " + cmd);
            if(cmd[0] == 'W') {
                toMainSerial.println("W");
                Serial.println("Main Beetle TX: W sent");
            }
            while(toMainSerial.available()) toMainSerial.read();
        }
        delay(100);
    }
    Serial.println("=== Main Beetle Handshake End ===");

    // Sub Beetle 핸드셰이크 (최대 10초)
    Serial.println("=== Sub Beetle Handshake Start ===");
    hsStart = millis();
    while(millis() - hsStart < 10000) {
        if(toSubSerial.available() > 0) {
            String cmd = toSubSerial.readStringUntil('\n');
            Serial.println("Sub Beetle RX: " + cmd);
            if(cmd[0] == 'W') {
                toSubSerial.println("W");
                Serial.println("Sub Beetle TX: W sent");
            }
            while(toSubSerial.available()) toSubSerial.read();
        }
        delay(100);
    }
    Serial.println("=== Sub Beetle Handshake End ===");
}
void loop() {
    ptrCurrentMode();
    TimerRun();
}
