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