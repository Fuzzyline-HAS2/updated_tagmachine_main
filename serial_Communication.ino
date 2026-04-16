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
    else if(command[0] == 'M'){
      digitalWrite(RELAY_PIN, HIGH);
      delay(500);
      digitalWrite(RELAY_PIN, LOW);
    }
    else if(command.length() >= 4){   // NFC 태그 데이터 (4자 이상이면 태그로 처리)
      mainRfidTagged = false;
      Serial.println("Sub Beetle Tag: " + command.substring(0,4));
      CheckingPlayers(command.substring(0,4));
      if(SubSerialTimerStart == true){
        SubSerialTimer.deleteTimer(subSerialTimerId);
        SubSerialTimerStart = false;
      }
      subSerialTimerId = SubSerialTimer.setInterval(1000,SubSerialTimerFunc);
      SubSerialTimerStart = true;
    }
    while(toSubSerial.available())
      toSubSerial.read();
  }
}

void SubSerialFlush(){
  while(toSubSerial.available())      //시리얼 통신 버퍼 flush
      toSubSerial.read();
}

void MainSerialFlush(){
  // SPI 통신으로 전환됨 (toMainSerial 제거)
}

/**
 * @brief Main PN532 직접 SPI 태그 읽기
 * WifiIntervalFunc 및 WhichTagged → ptrRfidMain 에서 호출
 */
void ReadMainNfc(){
  uint8_t uid[7];
  uint8_t uidLength;
  if (mainNfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 100)) {
    mainRfidTagged = true;
    String tagData = "";
    for (uint8_t i = 0; i < 4; i++) {
      tagData += (char)uid[i];
    }
    Serial.println("Main NFC Tag detected");
    CheckingPlayers(tagData);
  }
}