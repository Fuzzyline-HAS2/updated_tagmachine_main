#ifndef _LIBRARY_AND_PIN_
#define _LIBRARY_AND_PIN_

#include <Arduino.h>

#include <Adafruit_PN532.h>
#include <Adafruit_NeoPixel.h>
#include <HardwareSerial.h>
#include "DFRobotDFPlayerMini.h"
#include <HAS2_Wifi.h>
#include <SimpleTimer.h>

// #define DFPLAYER_RX_PIN 39
// #define DFPLAYER_TX_PIN 33
// #define BEETLE_RX_PIN 18
// #define BEETLE_TX_PIN 19

// #define PN532_SCK      14
// #define PN532_MISO     2
// #define PN532_MOSI     15
// #define PN532_SS1      13

// #define MAIN_LINE_NEOPIXEL_PIN       25
// #define MAIN_ROUND_NEOPIXEL_PIN      26
// #define SUB_LINE_NEOPIXEL_PIN       5
// #define SUB_ROUND_NEOPIXEL_PIN      23
// #define ONBOARD_NEOPIXEL_PIN    27

// #define RELAY_PIN  21


#define DFPLAYER_RX_PIN 39
#define DFPLAYER_TX_PIN 33
#define BEETLE_RX_PIN 19
#define BEETLE_TX_PIN 23

#define PN532_SCK      14
#define PN532_MISO     2
#define PN532_MOSI     15
#define PN532_SS1      13

#define MAIN_LINE_NEOPIXEL_PIN       25
#define MAIN_ROUND_NEOPIXEL_PIN      26
#define SUB_LINE_NEOPIXEL_PIN       5
#define SUB_ROUND_NEOPIXEL_PIN      18
#define ONBOARD_NEOPIXEL_PIN    27

#define RELAY_PIN  21
#endif
