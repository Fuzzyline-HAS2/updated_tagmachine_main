# 태그머신 수정 보고서

작성일: 2026-04-23

## 수정 요약

이번 수정은 술래가 잠긴 문을 해제하려고 할 때 보라색 게이지가 내려가다가 상태가 멈추는 문제를 해결하기 위한 작업이다.

핵심 변경은 태그 진행을 중간에 취소해야 하는 상황에서 단순히 `loginDone` 값만 바꾸지 않고, 타이머, RFID 콜백, 진행 카운터, 시리얼 버퍼를 한 번에 초기화하는 `CancelTagProgress()` 흐름을 추가한 것이다.

## 변경된 파일

### `timer.ino`

- `CancelTagProgress()` 함수를 추가했다.
- 이 함수는 태그 진행 중 비정상 상태가 감지되었을 때 다음 값을 초기화한다.
  - `GameTimer`
  - `SubSerialTimer`
  - `SubSerialTimerStart`
  - `gameTimerCnt`
  - `loginDone`
  - `ptrRfidMain`
  - `ptrRfidSub`
  - `ptrRfidMode`
  - `ptrRfidFail`
  - Sub/Main 시리얼 버퍼
- `TaggerUnlockTimerFunc()`에서 상태가 `lock`이 아닐 때 `loginDone = false`만 실행하던 부분을 `CancelTagProgress()` 호출로 변경했다.
- `NewbieTaggerUnlockTimerFunc()`도 같은 방식으로 변경했다.
- `SubSerialTimerFunc()`에서 타이머 종료 후 `SubSerialTimerStart`를 `true`가 아니라 `false`로 바꾸도록 수정했다.

### `rfid.ino`

- `UnlockFail()`에서 현재 상태가 `lock`이 아닐 때 `CancelTagProgress()`를 호출하도록 수정했다.
- `NewbieTaggerFail()`에서도 같은 방식으로 수정했다.
- 즉, 술래 잠금해제 실패나 뉴비모드 술래 실패 상황에서도 진행 상태가 확실히 정리되도록 했다.

### `updated_tagmachine_main.h`

- `CancelTagProgress()` 함수 선언을 추가했다.
- 다른 `.ino` 파일에서 이 함수를 호출할 수 있도록 프로토타입을 맞췄다.

### `Game_system.ino`

- `NewbiePlayerOpen()`에서 재생되는 효과음을 `VD7`에서 `VD1`로 변경했다.

## 보라색 게이지 멈춤 원인

문제가 발생한 구간은 술래 잠금해제 진행 흐름이다.

술래가 태그하면 `TaggerUnlockTimerFunc()` 또는 `NewbieTaggerUnlockTimerFunc()`가 실행되고, 이 함수 안에서 보라색 게이지가 `LineNeoDown(PURPLE, GREEN, ...)`으로 점점 줄어든다.

그런데 게이지가 내려가는 도중 서버/WiFi 상태를 다시 받아왔을 때 `strCurState`가 `"lock"`이 아니면 예전 코드는 아래처럼 처리했다.

```cpp
loginDone = false;
```

이 방식의 문제는 `loginDone`만 바꾸고 실제 진행 상태는 정리하지 않는다는 점이다.

즉, 게임 타이머, 서브 시리얼 타이머, RFID 모드, 실패 콜백, 진행 카운터, 시리얼 버퍼가 그대로 남아 있을 수 있었다. 그 결과 장치는 이미 실패/취소 상황인데도 내부 상태는 아직 태그 진행 중처럼 남아서, 보라색 게이지가 떨어지다가 갑자기 멈춘 것처럼 보였다.

## 해결 방식

상태가 `lock`이 아니게 된 순간을 "태그 진행 취소"로 보고 `CancelTagProgress()`를 호출하게 바꿨다.

```cpp
if(strCurState != "lock"){
    Serial.println("debuff on");
    CancelTagProgress();
}
```

`CancelTagProgress()`는 진행 중인 태그 시도를 완전히 정리한다.

```cpp
void CancelTagProgress(){
    GameTimer.deleteTimer(gameTimerId);
    SubSerialTimer.deleteTimer(subSerialTimerId);
    SubSerialTimerStart = false;
    gameTimerCnt = 0;
    loginDone = false;

    ptrRfidMain = CommnunicationMainBeetle;
    ptrRfidSub = CommnunicationBeetle;
    ptrRfidMode = Login;
    ptrRfidFail = WaitFunc;

    SubSerialFlush();
    MainSerialFlush();
    Serial.println("Cancel Tag Progress");
}
```

이제 보라색 게이지 진행 중 상태가 바뀌면, 남아 있는 타이머와 RFID 진행 상태가 모두 초기화된다. 그래서 게이지가 멈춘 채 장치가 애매한 상태에 남지 않고, 다시 정상 로그인/태그 대기 상태로 돌아간다.

## 컴파일 에러 해결 내용

기존에는 코드 여러 곳에서 `CancelTagProgress()`를 호출하고 있었지만, 링커가 찾을 수 있는 정확한 이름의 함수 정의가 없어서 아래 에러가 발생했다.

```text
undefined reference to `CancelTagProgress()'
```

이번 수정에서 `timer.ino`에 `CancelTagProgress()`를 정상 정의하고, `updated_tagmachine_main.h`에 선언을 추가해서 선언, 정의, 호출 이름이 모두 일치하게 했다.

## 기대 효과

- 술래 보라색 게이지 진행 중 상태가 바뀌어도 장치가 멈춘 상태로 남지 않는다.
- 실패/취소 상황에서 타이머와 RFID 모드가 안정적으로 초기화된다.
- `CancelTagProgress()` undefined reference 컴파일 에러가 해결된다.
- 뉴비모드 술래 흐름과 일반 술래 흐름이 같은 방식으로 정리된다.

## 커밋 정보

- 커밋: `3d2e42e`
- 메시지: `Fix tag progress cancellation flow`
- 브랜치: `beetle_2`
