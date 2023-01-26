#ifndef _DONE_ITEMBOX_CODE_
#define _DONE_ITEMBOX_CODE_

#include "Library_and_pin.h"
const int rfid_num = 1; // 설치된 pn532의 개수

//****************************************WIFI****************************************************************
HAS2_Wifi has2wifi;
void DataChanged();
void SettingFunc(void);
void ActivateFunc(void);
void ReadyFunc(void);
void GameSetting();
void WaitFunc();
void WifiIntervalLoop(unsigned long intervalValue);
unsigned long wifiInterval = 0;
//****************************************Pointer System****************************************************************
void (*ptrCurrentMode)();   //현재모드 저장용 포인터 함수
void (*ptrRfidMode)(char inputRole);      //rfid모드 저장용 포인터 함수
void (*ptrRfidFail)();      //rfidFaile모드 저장용 포인터 함수
void (*ptrRfidMain)();      //rfid 메인 저장용 포인터 함수
void (*ptrRfidSub)();      //rfid 서브 저장용 포인터 함수
void (*ptrGameTimer)();      //게임 타이머에 들어가는 포인터 함수
//****************************************Game System****************************************************************
volatile int playerLockTime = 7;
volatile int playerUnlockTime = 10;
volatile int taggerUnlockTime = 15;
volatile int ghostOpenTime = 15;
void WhichTagged();
void DoorOpen();
//****************************************Serial Communication*********************************************************
void CommnunicationBeetle();
void SubSerialFlush();
HardwareSerial toSubSerial(1); //
bool tagState = false;
//****************************************SimpleTimer SETUP****************************************************************
SimpleTimer GameTimer;
SimpleTimer WifiTimer;
SimpleTimer SubSerialTimer;

void TimerInit();
void WifiIntervalFunc();
void GameTimerFunc();
void SubSerialTimerFunc();

int wifiTimerId;
int gameTimerId;
int subSerialTimerId;

int gameTimerCnt = 0;
bool SubSerialTimerStart = false;
//****************************************DFPlayer SETUP****************************************************************
HardwareSerial MP3Serial(2);
DFRobotDFPlayerMini myDFPlayer;
void Mp3_Setup();
enum{VD1 = 1, VD2, VD3, VD4, VD5, VD6, VD7, VD8, VD9, VD10, VD11};
//****************************************Neopixel SETUP****************************************************************
void NeopixelInit();
void NeoBlink(int neo, int neoColor, int cnt, int blinkTime);
const int NumPixels[3] = {16,60,10};
const int NeopixelNum = 5;
enum {LINE = 0, ROUND, ONBOARD, LINE_SUB, ROUND_SUB};
enum {WHITE = 0, RED, YELLOW, GREEN, BLUE, PURPLE, BLACK, BLUE0, BLUE1, BLUE2, BLUE3};
// Neopixel 색상정보
int color[11][3] = {    {20, 20, 20},   //WHITE
                        {40, 0, 0},     //RED        
                        {40, 40, 0},    //YELLOW
                        {0, 40, 0},     //GREEN
                        {0, 0, 40},     //BLUE
                        {40, 0, 40},    //PURPLE
                        {0, 0, 0},      //BLACK
                        {0, 0, 20},     //ENCODERBLUE0
                        {0, 0, 40},     //ENCODERBLUE1
                        {0, 0, 60},     //ENCODERBLUE2
                        {0, 0, 80}};    //ENCODERBLUE3

const int neopixel_num = 5; // 설치된 네오픽셀의 개수

Adafruit_NeoPixel pixels[NeopixelNum] = {Adafruit_NeoPixel(NumPixels[LINE], MAIN_LINE_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800),
                                         Adafruit_NeoPixel(NumPixels[ROUND], MAIN_ROUND_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800),
                                         Adafruit_NeoPixel(NumPixels[ONBOARD], ONBOARD_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800),
                                         Adafruit_NeoPixel(NumPixels[LINE], SUB_LINE_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800),
                                         Adafruit_NeoPixel(NumPixels[ROUND], SUB_ROUND_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800)};
                                         
//****************************************RFID SETUP****************************************************************
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS1);

bool mainRfidTagged = false;

bool rfid_init_complete;
void RfidInit(void);
void RfidLoopMain(void);
void CheckingPlayers(uint8_t rfidData[32]);

void Login(char role);
void LoginTimerSelector(char role);
void LockFail();
void UnlockFail();
void WaitRfid(char role);

bool loginDone = false;     //처음 로그인 하면 true로 바뀌어서 wifi 안쓰게하기위함
char loginRole = 'P';        //처음 로그인 하고 나면 role 저장용.

#endif
