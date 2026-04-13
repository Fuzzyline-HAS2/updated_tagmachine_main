# updated_tagmachine_main
updated_tagmachine_main ESP32 코드

---

## DFPlayer Mini 수정 이력 (2026-03-30)

**증상:** tagmachine에서 DFPlayer 초기화 실패 → 소리 안 남 / 단독 테스트 코드에서는 정상 동작

### 수정 요약

| # | 파일 | 변경 내용 | 이유 |
|---|---|---|---|
| 1 | `updated_tagmachine_main.h` | `SoftwareSerial MP3Serial(RX,TX)` → `SoftwareSerial MP3Serial` | EspSoftwareSerial은 핀을 `begin()`에서 지정해야 함 |
| 2 | `dfplayer.ino` | `MP3Serial.begin(9600)` → `MP3Serial.begin(9600, SWSERIAL_8N1, RX, TX, false)` | 위와 동일, begin()에서 핀 지정 |
| 3 | `dfplayer.ino` | `setTimeOut(1000)` 제거 (begin 이전 호출) | 객체 미초기화 상태에서 타임아웃 설정 → 통신 오동작 |
| 4 | `dfplayer.ino` | `begin()` 전 `delay(2000)` 추가 | DFPlayer SD카드 마운트까지 1~2초 필요. 단독 테스트와 달리 tagmachine은 다른 init이 빠르게 끝나 대기 시간 부족 |
| 5 | `dfplayer.ino` | `begin(MP3Serial)` → `begin(MP3Serial, false)` | ACK 대기 비활성화. 복잡한 시스템에서 타이밍/노이즈로 ACK 유실 시 초기화 실패 방지 |
| 6 | `dfplayer.ino` | `begin()` 후 `delay(1000)` + 버퍼 비우기 추가 | DFPlayer가 초기화 완료 시 상태 패킷을 자동 전송 → 미비우면 이후 `available()` 오동작 |
| 7 | `neopixel.ino` | `lightColor()` 헬퍼 함수 추가 | `Adafruit_NeoPixel`에 없는 메서드 → 컴파일 에러 |

---

### 최종 `Mp3_Setup()`

```cpp
void Mp3_Setup(){
  MP3Serial.begin(9600, SWSERIAL_8N1, DFPLAYER_RX_PIN, DFPLAYER_TX_PIN, false);
  delay(2000);                               // DFPlayer 부팅 대기
  if (!myDFPlayer.begin(MP3Serial, false)) { // ACK 없이 초기화
    dfPlayerReady = false;
    return;
  }
  dfPlayerReady = true;
  myDFPlayer.volume(30);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  delay(1000);
  while (myDFPlayer.available()) myDFPlayer.read(); // 초기화 쓰레기 버퍼 비우기
}
```
