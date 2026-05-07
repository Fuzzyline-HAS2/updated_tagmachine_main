//****************************************mp3_setup()****************************************************************
bool dfPlayerReady = false;

void Mp3_Setup(){
  MP3Serial.begin(9600);
  DebugSerial.println("DFRobot DFPlayer Mini Demo");
  DebugSerial.println("Initializing DFPlayer ... (May take 3~5 seconds)");
  myDFPlayer.setTimeOut(1000);
  if (!myDFPlayer.begin(MP3Serial)) {
    DebugSerial.println("Unable to begin:");
    DebugSerial.println("1.Please recheck the connection!");
    DebugSerial.println("2.Please insert the SD card!");
    dfPlayerReady = false;
    DebugSerial.println("DFPlayer skipped. Continuing without audio.");
    return;  // begin 실패 시 후속 명령 건너뛰기
  }
  dfPlayerReady = true;
  DebugSerial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(30);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}//void MP3_SETUP


void Mp3PlayLargeFolder(uint8_t folder_number, uint16_t file_number)
{
  if(!dfPlayerReady) return;  // DFPlayer 미초기화 시 스킵
  static uint8_t play_error_count = 0; // MP3 파일이 처음 실행되면
  const char* lang = (const char *)my["selected_language"];
  if (lang != nullptr && String(lang) == "EN")
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
      DebugSerial.print("Error count: ");
      DebugSerial.println(play_error_count);
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