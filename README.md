# tagmachine_main
tagmachine_main ttgo 코드

---

## DFPlayer Mini 수정 이력 (2026-03-30)

### 문제
tagmachine 업로드 시 DFPlayer 초기화 실패 → 소리 안 남.
단독 테스트 코드(`DFPlayer_SWSerial_Test`)에서는 정상 동작.

---

### 변경 1 — SoftwareSerial 선언 방식 변경

**파일:** `tagmachine_main.h`, `dfplayer.ino`

| | 변경 전 | 변경 후 |
|---|---|---|
| 선언 | `SoftwareSerial MP3Serial(RX, TX);` | `SoftwareSerial MP3Serial;` |
| 초기화 | `MP3Serial.begin(9600);` | `MP3Serial.begin(9600, SWSERIAL_8N1, RX, TX, false);` |

**이유:**
EspSoftwareSerial 라이브러리는 핀을 생성자가 아닌 `begin()` 에서 지정하는 방식을 권장.
생성자에서 핀을 넣으면 `begin()` 시점에 핀 재설정이 제대로 안 될 수 있음.

---

### 변경 2 — `setTimeOut()` 제거 (begin 이전 호출 버그)

**파일:** `dfplayer.ino`

```cpp
// 변경 전 (버그)
myDFPlayer.setTimeOut(1000);   // begin() 이전에 호출 → 의미 없음 + 오동작
myDFPlayer.begin(MP3Serial);

// 변경 후
myDFPlayer.begin(MP3Serial, false);
```

**이유:**
`begin()` 전에 `setTimeOut()` 을 호출하면 DFPlayer 객체가 초기화되지 않은 상태에서 타임아웃이 설정되어 통신이 깨짐.

---

### 변경 3 — `delay(2000)` 추가 (부팅 대기)

**파일:** `dfplayer.ino`

```cpp
MP3Serial.begin(9600, SWSERIAL_8N1, RX, TX, false);
delay(2000);  // 추가
myDFPlayer.begin(MP3Serial, false);
```

**이유:**
DFPlayer는 전원 인가 후 SD카드 마운트까지 내부적으로 1~2초가 필요함.
단독 테스트 코드는 setup에서 DFPlayer만 초기화하므로 자연스럽게 시간이 확보되지만,
tagmachine은 NeoPixel, Timer, HardwareSerial 등의 초기화가 빠르게 끝나서
DFPlayer가 아직 준비되지 않은 상태에서 `begin()` 이 호출됨 → 초기화 실패.

---

### 변경 4 — `begin(MP3Serial, false)` ACK 비활성화

**파일:** `dfplayer.ino`

```cpp
// 변경 전
myDFPlayer.begin(MP3Serial);

// 변경 후
myDFPlayer.begin(MP3Serial, false);
```

**이유:**
두 번째 인자 `false` = ACK 응답을 기다리지 않음.
복잡한 시스템에서는 통신 노이즈나 타이밍으로 ACK 수신이 실패할 수 있어
ACK 없이도 초기화 성공으로 처리하도록 변경.

---

### 변경 5 — 초기화 후 버퍼 비우기 추가

**파일:** `dfplayer.ino`

```cpp
delay(1000);
while (myDFPlayer.available()) myDFPlayer.read();  // 추가
```

**이유:**
DFPlayer는 초기화 완료 시 상태 바이트를 시리얼로 자동 전송함.
이를 비우지 않으면 이후 `available()` 체크 시 쓰레기값이 남아 오동작 가능.

---

### 변경 6 — `lightColor()` 헬퍼 함수 추가

**파일:** `neopixel.ino`

```cpp
void lightColor(Adafruit_NeoPixel& strip, int* col) {
  strip.fill(strip.Color(col[0], col[1], col[2]));
  strip.show();
}
```

**이유:**
`Adafruit_NeoPixel` 라이브러리에는 `lightColor()` 메서드가 없음.
기존 코드 전체에서 `pixels[X].lightColor(color[Y])` 형태로 사용 중이었으나 컴파일 에러 발생.
헬퍼 함수로 분리하고 `lightColor(pixels[X], color[Y])` 형태로 모두 교체.

---

### 최종 `Mp3_Setup()` 코드

```cpp
void Mp3_Setup(){
  MP3Serial.begin(9600, SWSERIAL_8N1, DFPLAYER_RX_PIN, DFPLAYER_TX_PIN, false);
  delay(2000);                          // DFPlayer 부팅 대기
  Serial.println("Initializing DFPlayer ...");
  if (!myDFPlayer.begin(MP3Serial, false)) {  // ACK 없이 초기화
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
}
```
