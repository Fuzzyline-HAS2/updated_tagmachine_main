#include <Arduino.h>
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\tagmachine_main_geekble.ino"
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

#line 14 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\tagmachine_main_geekble.ino"
void setup();
#line 27 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\tagmachine_main_geekble.ino"
void loop();
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Game_system.ino"
void WhichTagged();
#line 7 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Game_system.ino"
void DoorOpen();
#line 21 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Game_system.ino"
void GhostDoorOpen();
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Wifi.ino"
void DataChanged();
#line 45 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Wifi.ino"
void WaitFunc();
#line 48 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Wifi.ino"
void SettingFunc(void);
#line 62 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Wifi.ino"
void ActivateFunc(void);
#line 78 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Wifi.ino"
void ReadyFunc(void);
#line 91 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Wifi.ino"
void GameSetting();
#line 2 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\dfplayer.ino"
void Mp3_Setup();
#line 24 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\dfplayer.ino"
void Mp3PlayLargeFolder(uint8_t folder_number, uint16_t file_number);
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void NeopixelInit();
#line 13 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void NeoBlink(int neo, int neoColor, int cnt, int blinkTime);
#line 24 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void AllNeoOn(int neoColor);
#line 29 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void LineNeoDown(int changeColr, int baseColor, int cnt);
#line 41 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void LineNeoUp(int changeColr, int baseColor, int cnt);
#line 53 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void RoundNeoEffect(int neocolor);
#line 71 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void RoundNeoEffectDown(int neocolor);
#line 85 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void RoundNeoToggle(int neoColor, int toggle);
#line 95 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void LineNeoToggle(int neoColor, int toggle);
#line 106 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void RoundNeoUp(int changeColr, int baseColor, int cnt);
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void RfidInit();
#line 21 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void RfidLoopMain();
#line 48 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void CheckingPlayers(String tagUser);
#line 95 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void Login(char role);
#line 120 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void WaitRfid(char role);
#line 124 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void LoginTimerSelector(char role);
#line 205 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void LockFail();
#line 225 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void UnlockFail();
#line 243 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void GhostOpenFailUnlock();
#line 259 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void GhostOpenFailLock();
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\serial_Communication.ino"
void CommnunicationBeetle();
#line 36 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\serial_Communication.ino"
void SubSerialFlush();
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void TimerInit();
#line 10 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void TimerRun();
#line 20 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void WifiIntervalFunc();
#line 28 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void GameTimerFunc();
#line 36 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void SubSerialTimerFunc();
#line 43 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void DebuffTimerFunc();
#line 53 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void ReturnNormalState();
#line 73 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void PlayerLockTimerFunc();
#line 105 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void PlayerUnlockTimerFunc();
#line 137 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void TaggerUnlockTimerFunc();
#line 169 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void GhostUnlockTimerFunc();
#line 204 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void GhostLockTimerFunc();
#line 14 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\tagmachine_main_geekble.ino"
void setup() {
    Serial.begin(115200);
    toSubSerial.begin(9600, SERIAL_8N1, BEETLE_RX_PIN, BEETLE_TX_PIN);
    NeopixelInit();
    RfidInit();
    TimerInit();
    Mp3_Setup();
    pinMode(RELAY_PIN, OUTPUT);
    has2wifi.Setup("city");
//     has2wifi.Setup("badland");
    DataChanged();
    GameSetting();
}
void loop() {
    ptrCurrentMode();
    TimerRun();
}

#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Game_system.ino"
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
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\Wifi.ino"
void DataChanged()
{
  static StaticJsonDocument<500> cur;   //저장되어 있는 cur과 읽어온 my 값과 비교후 실행
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
    if((String)(const char*)my["device_state"] == "lock"){ 
      strCurState = "lock";
      AllNeoOn(GREEN);
    }
    else if((String)(const char*)my["device_state"] == "mo"){ 
        digitalWrite(RELAY_PIN, HIGH);
        delay(1000);
        digitalWrite(RELAY_PIN, LOW);
        has2wifi.Send((String)(const char*)my["device_name"], "device_state", (String)(const char*)cur["device_state"]);
    }
    else if((String)(const char*)my["device_state"] == "activate"){
        strCurState = "activate";
        ActivateFunc();
    }
  }
  if((String)(const char*)my["device_state"] == "debuff"){ 
    strCurState = "debuff";
    ptrRfidFail = WaitFunc;
    AllNeoOn(PURPLE);
    Serial.println("디버프 시작");
    DebuffTimer.deleteTimer(debuffTimerId);
    debuffTimerId = DebuffTimer.setInterval(60000,DebuffTimerFunc);
    ReturnNormalState();
  }
  cur = my; // cur 데이터 그룹에 현재 읽어온 데이터 저장
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
    ptrRfidMain = RfidLoopMain;
    ptrRfidSub = CommnunicationBeetle;
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
}
void GameSetting(){
    playerLockTime = (int)my["player_lock_time"];
    playerUnlockTime = (int)my["player_unlock_time"];
    taggerUnlockTime = (int)my["tagger_unlock_time"];
    ghostOpenTime = (int)my["ghost_open_time"];
}
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\dfplayer.ino"
//****************************************mp3_setup()****************************************************************
void Mp3_Setup(){
  //Serial.println();
  MP3Serial.begin(9600, SERIAL_8N1, DFPLAYER_RX_PIN, DFPLAYER_TX_PIN); 
  Serial.println("DFRobot DFPlayer Mini Demo");
  Serial.println("Initializing DFPlayer ... (May take 3~5 seconds)");
  myDFPlayer.setTimeOut(1000); //Set serial communictaion time out 1000 ms
  if (!myDFPlayer.begin(MP3Serial)) { //Use softwareSerial to communicate with mp3.
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    // while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  myDFPlayer.volume(30);  //Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //myDFPlayer.enableDAC();  //Enable On-chip DAC
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

}//void MP3_SETUP


void Mp3PlayLargeFolder(uint8_t folder_number, uint16_t file_number)
{
  static uint8_t play_error_count = 0; // MP3 파일이 처음 실행되면
  if ((String)(const char *)shift_machine["selected_language"] == "EN")
  {
    folder_number = 2 + folder_number;
  }
  if (myDFPlayer.available())
  {
    myDFPlayer.playLargeFolder(folder_number, file_number);
    play_error_count = 0;
  }
  else
  {
    if (play_error_count < 3)
    {
      myDFPlayer.playLargeFolder(folder_number, file_number);
      play_error_count++;
      Serial.print("에러횟수 :");
      Serial.println(play_error_count);
    }
    else
    {
      if (!(send_mp3_err))
      {
        send_mp3_err = true;
        has2wifi.Send((String)(const char *)my["device_name"], "device_state", "MP3");
      }
    }
  }
}
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\neopixel.ino"
void NeopixelInit()
{
  for (int i = 0; i < NeopixelNum; ++i)
  {
    pixels[i].begin();
  }
  for (int i = 0; i < NeopixelNum; ++i)
  {
    pixels[i].lightColor(color[WHITE]);
  }
}

void NeoBlink(int neo, int neoColor, int cnt, int blinkTime){
    for(int i = 0; i < cnt; i++){                          //0.5*10=5초동안 점멸
        pixels[neo].lightColor(color[BLACK]); //전체 off
        pixels[neo+3].lightColor(color[BLACK]);
        delay(blinkTime);            
        pixels[neo].lightColor(color[neoColor]); //전체 적색on
        pixels[neo+3].lightColor(color[neoColor]);
        delay(blinkTime);                   //전체 적색on
    }
}

void AllNeoOn(int neoColor){
    for (int i = 0; i < NeopixelNum; ++i)
        pixels[i].lightColor(color[neoColor]);
}

void LineNeoDown(int changeColr, int baseColor, int cnt){
  for(int i = 0; i < NumPixels[LINE]; i++){
    pixels[LINE].setPixelColor(i,pixels[LINE].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
    pixels[LINE_SUB].setPixelColor(i,pixels[LINE_SUB].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
  }
  for(int i = 0; i < cnt; i++){
    pixels[LINE].setPixelColor(i,pixels[LINE].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
    pixels[LINE_SUB].setPixelColor(i,pixels[LINE_SUB].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
  }
  pixels[LINE].show();
  pixels[LINE_SUB].show();
}
void LineNeoUp(int changeColr, int baseColor, int cnt){
  for(int i = 0; i < NumPixels[LINE]; i++){
    pixels[LINE].setPixelColor(i,pixels[LINE].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
    pixels[LINE_SUB].setPixelColor(i,pixels[LINE_SUB].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
  }
  for(int i = 16; i > 16 - cnt; i--){
    pixels[LINE].setPixelColor(i,pixels[LINE].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
    pixels[LINE_SUB].setPixelColor(i,pixels[LINE_SUB].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
  }
  pixels[LINE].show();
  pixels[LINE_SUB].show();
}
void RoundNeoEffect(int neocolor)
{
  pixels[ROUND].clear();
  pixels[ROUND_SUB].clear();
  pixels[ROUND].show();
  pixels[ROUND_SUB].show();

  for(int i = 0; i < NumPixels[ROUND]/2; i++)
  {
    pixels[ROUND].setPixelColor(i,pixels[ROUND].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND].setPixelColor(NumPixels[ROUND]-i,pixels[ROUND].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND_SUB].setPixelColor(i,pixels[ROUND_SUB].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND_SUB].setPixelColor(NumPixels[ROUND]-i,pixels[ROUND_SUB].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND].show();
    pixels[ROUND_SUB].show();
    delay(100);
  }
}
void RoundNeoEffectDown(int neocolor)
{
  for(int i = NumPixels[ROUND]/2; i >= 0; i--)
  {
    pixels[ROUND].setPixelColor(i,pixels[ROUND].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND].setPixelColor(NumPixels[ROUND]-i,pixels[ROUND].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND_SUB].setPixelColor(i,pixels[ROUND_SUB].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND_SUB].setPixelColor(NumPixels[ROUND]-i,pixels[ROUND_SUB].Color(color[neocolor][0],color[neocolor][1],color[neocolor][2]));
    pixels[ROUND].show();
    pixels[ROUND_SUB].show();
    delay(100);
  }
}

void RoundNeoToggle(int neoColor, int toggle){
  if(toggle%2 == 1){
    pixels[ROUND].lightColor(color[neoColor]);
    pixels[ROUND_SUB].lightColor(color[neoColor]);
  }
  else{
    pixels[ROUND].lightColor(color[BLACK]);
    pixels[ROUND_SUB].lightColor(color[BLACK]);
  }
}
void LineNeoToggle(int neoColor, int toggle){
  if(toggle%2 == 1){
    pixels[LINE].lightColor(color[neoColor]);
    pixels[LINE_SUB].lightColor(color[neoColor]);
  }
  else{
    pixels[LINE].lightColor(color[BLACK]);
    pixels[LINE_SUB].lightColor(color[BLACK]);
  }
}

void RoundNeoUp(int changeColr, int baseColor, int cnt){
  for(int i = 0; i < 30; i++){
    pixels[ROUND].setPixelColor(i,pixels[ROUND].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
    pixels[ROUND_SUB].setPixelColor(i,pixels[ROUND_SUB].Color(color[baseColor][0],color[baseColor][1],color[baseColor][2]));
  }
  for(int i = 0; i < cnt; i++){
    pixels[ROUND].setPixelColor(i,pixels[ROUND].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
    pixels[ROUND_SUB].setPixelColor(i,pixels[ROUND_SUB].Color(color[changeColr][0],color[changeColr][1],color[changeColr][2]));
  }
  pixels[ROUND].show();
  pixels[ROUND_SUB].show();
}
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\rfid.ino"
void RfidInit()
{
  RestartPn532:
  nfc.begin();
  if (!(nfc.getFirmwareVersion()))
  {
    Serial.print("PN532 연결실패");
    AllNeoOn(RED);
    goto RestartPn532;
  }
  else
  {
    nfc.SAMConfig();
    Serial.print("PN532 연결성공");
    rfid_init_complete = true;
    AllNeoOn(YELLOW);
  }
  delay(100);
}

void RfidLoopMain()
{
  uint8_t uid[3][7] = {{0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0}}; // Buffer to store the returned UID
  uint8_t uidLength[] = {0};                   // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t data[32];
  byte pn532_packetbuffer11[64];
  pn532_packetbuffer11[0] = 0x00;
  mainRfidTagged = true;
  if (nfc.sendCommandCheckAck(pn532_packetbuffer11, 1)){ // rfid 통신 가능한 상태인지 확인
    if (nfc.startPassiveTargetIDDetection(PN532_MIFARE_ISO14443A)){                                       // rfid에 tag 찍혔는지 확인용 //데이터 들어오면 uid정보 가져오기
      if (nfc.ntag2xx_ReadPage(7, data)){ // ntag 데이터에 접근해서 불러와서 data행열에 저장
        Serial.println("TAGGGED");
        String tagUser = "";
        for(int i = 0; i < 4; i++)    //GxPx 데이터만 배열에서 추출해서 string으로 저장
          tagUser += (char)data[i];
        CheckingPlayers(tagUser);
      }
    }
    else
    {
      ptrRfidFail();
    }
  }
}

void CheckingPlayers(String tagUser) //어떤 카드가 들어왔는지 확인용
{ 
  Serial.println("tag_user_data : " + tagUser);     // 1. 태그한 플레이어의 역할과 생명칩갯수, 최대생명칩갯수 등 읽어오기
  if(tagUser == "MMMM"){  //스태프카드 
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
    digitalWrite(RELAY_PIN, LOW);
  }
  else{
    if(loginDone == false)                            // 로그인할때만 체크함
    {
      has2wifi.Receive(tagUser);                      // 2. 술래인지, 플레이어인지 구분
      if((String)(const char*)tag["role"] == "player"){ // 3. 태그한 사용자가 플레이어고
        Serial.println("Player Tagged");
        loginRole = 'P';
        ptrRfidMode('P');
      }
      else if((String)(const char*)tag["role"] == "tagger"){ // 3. 태그한 사용자가 플레이어고
        Serial.println("Tagger Tagged");
        loginRole = 'T';
        ptrRfidMode('T');
      }
      else if((String)(const char*)tag["role"] == "ghost" || (String)(const char*)tag["role"] == "revival"){ // 3. 태그한 
        Serial.println("Ghost Tagged");
        loginRole = 'G';
        ptrRfidMode('G');
      }
      else{ 
        Serial.println("Wrong TAG");
      }
    }
    else
    {
      if(strLastTagUser == tagUser){  //Login 진행한 태그와 같은지 확인
        Serial.println("LoginRole: " + String(loginRole));
        ptrRfidMode(loginRole);
      }
      else{
        Serial.println("Different TAG deteced");
        ptrRfidFail();
      }
    }
    strLastTagUser = tagUser;
  }
  
}

void Login(char role)
{ 
  Serial.println("LOGIN");
  loginDone = true;
  pixels[ROUND].lightColor(color[BLACK]);
  pixels[ROUND_SUB].lightColor(color[BLACK]);

  GameTimer.deleteTimer(gameTimerId);
  gameTimerId = GameTimer.setInterval(1000,GameTimerFunc);
  WifiTimer.deleteTimer(wifiTimerId); 
  gameTimerCnt = 0;
  if(mainRfidTagged == true)
  {
    ptrRfidMain = RfidLoopMain;
    ptrRfidSub = WaitFunc;
    LoginTimerSelector(role);
  }
  else if(mainRfidTagged == false)
  {
    ptrRfidMain = WaitFunc;
    ptrRfidSub = CommnunicationBeetle;
    LoginTimerSelector(role);
  }
}

void WaitRfid(char role)
{
  Serial.println("WAIT RFID");
}
void LoginTimerSelector(char role){
  Serial.println("LoginTimerSelector");
  if((String)(const char*)my["device_state"] == "lock")
  {
    if(role == 'P')       
    {
      ptrGameTimer = PlayerUnlockTimerFunc;
      ptrRfidFail = UnlockFail;
      ptrRfidMode = WaitRfid;
    }
    else if(role == 'G')  
    {
      ptrGameTimer = GhostUnlockTimerFunc;
      ptrRfidFail = GhostOpenFailLock;
      ptrRfidMode = WaitRfid; 
    }
    else if(role == 'T')  
    {
      ptrGameTimer = TaggerUnlockTimerFunc;
      ptrRfidFail = UnlockFail;
      ptrRfidMode = WaitRfid;
    }
  }
  else if((String)(const char*)my["device_state"] == "debuff")
  {
    AllNeoOn(PURPLE);
    if(role == 'P')       
    {
      NeoBlink(ROUND,RED,2,400);
      AllNeoOn(PURPLE);
      ReturnNormalState(); 
    }
    else if(role == 'G')  
    {
      NeoBlink(ROUND,RED,2,400);
      AllNeoOn(PURPLE);
      ReturnNormalState(); 
    }
    else if(role == 'T')  
    {
      Mp3PlayLargeFolder(1, VD1);
      Serial.println("Tagger Door Open");
      digitalWrite(RELAY_PIN, HIGH);  
  
      RoundNeoEffect(PURPLE);
      AllNeoOn(PURPLE);
      RoundNeoEffectDown(BLACK);
      DoorOpen();
      ReturnNormalState();                                                       //시리얼 통신 버퍼 flush
      AllNeoOn(PURPLE);
    }
  }
  else  //도어 UNLOCK 일때
  {
    if(role == 'P')       
    {
      Serial.println("LoginTimerSelector PlayerSelected");
      ptrGameTimer = PlayerLockTimerFunc;
      ptrRfidFail = LockFail;
      ptrRfidMode = WaitRfid;
    }
    else if(role == 'G')  
    {
      ptrGameTimer = GhostLockTimerFunc;
      ptrRfidFail = GhostOpenFailUnlock;
      ptrRfidMode = WaitRfid;
    }
    else if(role == 'T') 
    {
      Mp3PlayLargeFolder(1, VD1);
      Serial.println("Tagger Door Open");
      digitalWrite(RELAY_PIN, HIGH);  
      has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
      RoundNeoEffect(PURPLE);
      AllNeoOn(PURPLE);
      DoorOpen();
      AllNeoOn(YELLOW);
      ReturnNormalState();
    }
  }
}
void LockFail()
{ 
  has2wifi.ReceiveMine();
  DataChanged();
  // Serial.println("strCurState:" + String(strCurState));
  if(strCurState != "activate"){
      Serial.println("debuff on");
      loginDone = false;
  }
  else{
    Mp3PlayLargeFolder(1, VD1);
    Serial.println("Lock Fail Door Open");
    digitalWrite(RELAY_PIN, HIGH);
    has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
    RoundNeoEffect(YELLOW);
    AllNeoOn(YELLOW);
    DoorOpen();
    ReturnNormalState();
  }
}
void UnlockFail()
{ 
  has2wifi.ReceiveMine();
  DataChanged();
  // Serial.println("strCurState:" + String(strCurState));
  if(strCurState != "lock"){
      Serial.println("debuff on");
      loginDone = false;
  }
  else{
    Mp3PlayLargeFolder(1, VD6);
    Serial.println("Unlock Fail Door Shut");
    NeoBlink(ROUND,RED,5,500);
    AllNeoOn(GREEN);
    ReturnNormalState();
  }
}

void GhostOpenFailUnlock()
{ 
  // has2wifi.ReceiveMine();
  // DataChanged();
  // // Serial.println("strCurState:" + String(strCurState));
  // if(strCurState != "lock"){
  //     Serial.println("debuff on");
  // }
  // else{
  Mp3PlayLargeFolder(1, VD6);
  Serial.println("Ghost Door OpenFail");
  NeoBlink(ROUND,RED,5,500);
  AllNeoOn(YELLOW);
  ReturnNormalState();
  // // }
}
void GhostOpenFailLock()
{ 
  // has2wifi.ReceiveMine();
  // DataChanged();
  // // Serial.println("strCurState:" + String(strCurState));
  // if(strCurState != "activate"){
  //     Serial.println("debuff on");
  // }
  // else{
  Mp3PlayLargeFolder(1, VD6);
  Serial.println("Unlock Fail Door Shut");
  NeoBlink(ROUND,RED,5,500);
  AllNeoOn(GREEN);
  ReturnNormalState();
  // }
}

#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\serial_Communication.ino"
void CommnunicationBeetle(){
  // Serial.println("READ");
  if(toSubSerial.available() > 0){
    String command = toSubSerial.readStringUntil('\n'); //추가 시리얼의 값을 수신하여 String으로 저장
    Serial.println(command);
    // Serial.println("received:" + String(command[0])); //기본 시리얼에 추가 시리얼 내용을 출력
    
    if(command[0] == 'W'){
      Serial.println("Beetle Init Success");
      toSubSerial.println("W");
    }
    else if(command[0] == 'R'){
      Serial.println("Beetle Reset Success");
    }
    else if(command[0] == 'G'){   // Packet ex.  "T1:GxP0_T2:GxP0_T3:GxP0"
      mainRfidTagged = false;
      Serial.println(command.substring(0,4));
      CheckingPlayers(command.substring(0,4));
      if(SubSerialTimerStart == true){
        SubSerialTimer.deleteTimer(subSerialTimerId);
        SubSerialTimerStart = false;
      }
      subSerialTimerId = SubSerialTimer.setInterval(1000,SubSerialTimerFunc);
      SubSerialTimerStart = true;
    }
    else if(command[0] == 'M'){
      digitalWrite(RELAY_PIN, HIGH);
      delay(500);
      digitalWrite(RELAY_PIN, LOW);
    }
    while(toSubSerial.available())
      toSubSerial.read();
  }
}

void SubSerialFlush(){
  while(toSubSerial.available())      //시리얼 통신 버퍼 flush
      toSubSerial.read();
}
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\HAS2_Code\\HAS2_Final_Code\\tagmachine_main_geekble\\timer.ino"
void TimerInit(){
    wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);
    // gameTimerId = GameTimer.setInterval(500,GameTimerFunc);
    // GameTimer.deleteTimer(gameTimerId);
    // subSerialTimerId = SubSerialTimer.setInterval(1000,SubSerialTimerFunc);
    // SubSerialTimer.deleteTimer(subSerialTimerId);
    // debuffTimerId = DebuffTimer.setInterval(1000,DebuffTimerFunc);
    // DebuffTimer.deleteTimer(debuffTimerId);
}
void TimerRun(){
    WifiTimer.run();
    GameTimer.run();
    SubSerialTimer.run();
    DebuffTimer.run();
}

/**
 * @brief WIFI read 타이머 주기별로 받는 함수
 */
void WifiIntervalFunc(){
    has2wifi.Loop(DataChanged);
    CommnunicationBeetle();
}

/**
 * @brief 다중 태그를 인식하기 위한 타이머 함수
 */
void GameTimerFunc(){
    Serial.println("GameTimer");
    ptrGameTimer();
}

/**
 * @brief 반대쪽 SUB 태그머신(Beetle)에서 데이터를 타이머 주기별로 받는 함수
 */
void SubSerialTimerFunc(){
    SubSerialTimer.deleteTimer(subSerialTimerId);
    SubSerialTimerStart = true;
    ptrRfidFail();
    while(toSubSerial.available())
      toSubSerial.read();
}
void DebuffTimerFunc(){
    DebuffTimer.deleteTimer(debuffTimerId);
    Serial.println("debuff time end");
    has2wifi.Send((String)(const char*)my["device_name"], "device_state", "activate");
    ReturnNormalState();
}

/**
 * @brief 일반 상태로 돌아가는 함수
 */
void ReturnNormalState(){           
    ptrRfidMain = RfidLoopMain;
    ptrRfidSub = CommnunicationBeetle;
    ptrRfidMode = Login;
    ptrRfidFail = WaitFunc;
    gameTimerCnt = 0;

    loginDone = false;
    GameTimer.deleteTimer(gameTimerId); 
    SubSerialTimer.deleteTimer(subSerialTimerId);   
    WifiTimer.deleteTimer(wifiTimerId);                                          //게임 타이머 종료
    wifiTimerId = WifiTimer.setInterval(2000,WifiIntervalFunc);
    
    Serial.println("Return Normal State");
    SubSerialFlush();                                                               //시리얼 통신 버퍼 flush
}

/** 
 * @brief 잠기지 않은 도어를 플레이어가 도어가 잠금을 하기위한 함수
 */
void PlayerLockTimerFunc(){
    gameTimerCnt++;
    RoundNeoToggle(GREEN,gameTimerCnt);
    LineNeoUp(GREEN, YELLOW, map(gameTimerCnt,0,playerLockTime,0,NumPixels[LINE]));
    Serial.println(map(gameTimerCnt,0,playerLockTime,0,NumPixels[LINE]));
    if(gameTimerCnt == 1)                                                         // 3번마다 "도어잠금 효과음" 나오게 하기
        Mp3PlayLargeFolder(1, VD11);
    if(gameTimerCnt > (playerLockTime))
    {
        has2wifi.ReceiveMine();
        DataChanged();
        // Serial.println("strCurState:" + String(strCurState));
        if(strCurState != "activate"){
            Serial.println("debuff on");
            loginDone = false;
        }
        else {
            Serial.println("debuff off");
            has2wifi.Send((String)(const char*)my["device_name"], "device_state", "lock");
            Serial.println("DOOR LOCK!");
            Mp3PlayLargeFolder(1, VD4);
            has2wifi.ReceiveMine();
            ReturnNormalState();
            RoundNeoEffect(GREEN);
            SubSerialFlush();         
        }                                                     //시리얼 통신 버퍼 flush
    }
}

/**
 * @brief 잠겨있는 도어를 플레이어가 잠금해제를 하기위한 함수
 */
void PlayerUnlockTimerFunc(){       
    gameTimerCnt++;
    RoundNeoToggle(GREEN,gameTimerCnt);
    LineNeoDown(YELLOW, GREEN, map(gameTimerCnt,0,playerUnlockTime,0,NumPixels[LINE]));
    if(gameTimerCnt == 1)                                                         // 3번마다 "도어잠금 효과음" 나오게 하기
        Mp3PlayLargeFolder(1, VD11);
    if(gameTimerCnt > (playerUnlockTime))
    {
        has2wifi.ReceiveMine();
        DataChanged();
        // Serial.println("strCurState:" + String(strCurState));
        if(strCurState != "lock"){
            Serial.println("debuff on");
            loginDone = false;
        }
        else {
            Serial.println("DOOR UNLOCK!");
            Mp3PlayLargeFolder(1, VD7);
            ReturnNormalState();
            digitalWrite(RELAY_PIN, HIGH);
            has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
            RoundNeoEffect(YELLOW);
            DoorOpen();
            has2wifi.ReceiveMine();
            SubSerialFlush();    
        }                                                       //시리얼 통신 버퍼 flush
    }
}

/**
 * @brief 잠겨있는 도어를 술래가 잠금해제를 하기위한 함수
 */
void TaggerUnlockTimerFunc(){
    gameTimerCnt++;
    RoundNeoToggle(PURPLE,gameTimerCnt);
    if(gameTimerCnt%3 == 1)                                                         // 3번마다 "술래 침입시도" 나오게 하기
        if(gameTimerCnt < (taggerUnlockTime - 2))                                   // 마지막에는 효과음 안나오게 해서 짤리지 않게 하는 함수
            Mp3PlayLargeFolder(1, VD10);
    LineNeoDown(PURPLE, GREEN, map(gameTimerCnt,0,taggerUnlockTime,0,NumPixels[LINE]));
    if(gameTimerCnt > (taggerUnlockTime))
    {
        has2wifi.ReceiveMine();
        DataChanged();
        // Serial.println("strCurState:" + String(strCurState));
        if(strCurState != "lock"){
            Serial.println("debuff on");
            loginDone = false;
        }
        else {
            Mp3PlayLargeFolder(1, VD1);
            Serial.println("DOOR UNLOCK!");
            ReturnNormalState();
            digitalWrite(RELAY_PIN, HIGH); 
            has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
            RoundNeoEffect(PURPLE);
            DoorOpen();
            SubSerialFlush(); 
        }                                                          //시리얼 통신 버퍼 flush
    }
}

/**
 * @brief 잠겨있는 도어를 유령이 잠금해제를 하기위한 함수
 */
void GhostUnlockTimerFunc(){                                                
    gameTimerCnt++;
    // RoundNeoToggle(BLUE,gameTimerCnt);
    // LineNeoDown(BLUE, GREEN, map(gameTimerCnt,0,ghostOpenTime,0,NumPixels[LINE]));
    RoundNeoUp(BLUE, GREEN, map(gameTimerCnt,0,ghostOpenTime,0,NumPixels[ROUND]/2));
    if(gameTimerCnt > (ghostOpenTime))
    {
        has2wifi.ReceiveMine();
        DataChanged();
        // Serial.println("strCurState:" + String(strCurState));
        if(strCurState != "lock"){
            Serial.println("debuff on");
            loginDone = false;
        }
        else{
            Mp3PlayLargeFolder(1, VD1);
            Serial.println("GHOST OPEN");
            ReturnNormalState();
            digitalWrite(RELAY_PIN, HIGH);
            has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
            RoundNeoEffect(BLUE);
            GhostDoorOpen();
            has2wifi.Send((String)(const char*)my["device_name"], "device_state", "lock");
            AllNeoOn(GREEN);
            SubSerialFlush();                                                        //시리얼 통신 버퍼 flush
            delay(1000);
            has2wifi.Loop(DataChanged); //LOCK -> ACTIVATE 바뀐것을 업데이트 받기 위함
        }
    }
    
}

/**
 * @brief 잠겨있지 않은 도어 유령이 잠금해제를 하기위한 함수
 */
void GhostLockTimerFunc(){      
    gameTimerCnt++;
    // RoundNeoToggle(BLUE,gameTimerCnt);
    // LineNeoUp(BLUE, YELLOW, map(gameTimerCnt,0,ghostOpenTime,0,NumPixels[LINE]));
    RoundNeoUp(BLUE, YELLOW, map(gameTimerCnt,0,ghostOpenTime,0,NumPixels[ROUND]/2));
    if(gameTimerCnt > (ghostOpenTime))
    {
        has2wifi.ReceiveMine();
        DataChanged();
        // Serial.println("strCurState:" + String(strCurState));
        if(strCurState != "activate"){
            Serial.println("debuff on");
        }
        else {
            Mp3PlayLargeFolder(1, VD1);
            Serial.println("GHOST OPEN");
            ReturnNormalState();
            digitalWrite(RELAY_PIN, HIGH);
            has2wifi.Send((String)(const char*)my["device_name"], "device_state", "open");
            RoundNeoEffect(BLUE);
            GhostDoorOpen();
            has2wifi.Send((String)(const char*)my["device_name"], "device_state", "activate");
            AllNeoOn(YELLOW);
            SubSerialFlush();                                                           //시리얼 통신 버퍼 flush
            delay(1000);
            has2wifi.Loop(DataChanged); //LOCK -> ACTIVATE 바뀐것을 업데이트 받기 위함
        }
    }
}

