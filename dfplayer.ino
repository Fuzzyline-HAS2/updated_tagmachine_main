//****************************************mp3_setup()****************************************************************
bool dfPlayerReady = false;

void Mp3_Setup(){
  MP3Serial.begin(9600, SWSERIAL_8N1, DFPLAYER_RX_PIN, DFPLAYER_TX_PIN, false);
  delay(2000);  // DFPlayer 전원 인가 후 부팅 대기
  Serial.println("Initializing DFPlayer ...");
  if (!myDFPlayer.begin(MP3Serial, false)) {  // false = ACK 없이 초기화
    Serial.println("DFPlayer 초기화 실패 - 배선/SD카드 확인");
    dfPlayerReady = false;
    return;
  }
  dfPlayerReady = true;
  Serial.println("DFPlayer Mini online.");
  myDFPlayer.volume(30);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  delay(1000);
  while (myDFPlayer.available()) myDFPlayer.read();  // 버퍼 비우기
}//void MP3_SETUP


void Mp3PlayLargeFolder(uint8_t folder_number, uint16_t file_number)
{
  if(!dfPlayerReady) return;  // DFPlayer 미초기화 시 스킵
  static uint8_t play_error_count = 0; // MP3 파일이 처음 실행되면
  const char* lang = (const char *)shift_machine["selected_language"];
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