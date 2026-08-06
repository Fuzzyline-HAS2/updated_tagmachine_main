"""TTGO T1을 꽂으면 포트를 자동 인식해 build/ 결과물을 업로드한다.

사용법:
    python3 scripts/upload.py

Arduino IDE / arduino-cli 로 빌드해 둔 결과물을 그대로 굽는다.
(부트로더 + 파티션 테이블 + boot_app0 + 앱 전체 플래싱)
"""

import glob
import os
import subprocess
import sys
import time

sys.stdout.reconfigure(encoding="utf-8")

# 보드 기본값 921600 은 이 USB 시리얼 어댑터에서 불안정.
# 460800 이 실패하면(2.3% 지점 "Lost connection") 아래를 115200 으로 낮춘다.
FQBN = "esp32:esp32:ttgo-t1:UploadSpeed=460800"
SKETCH_NAME = "updated_tagmachine_main"
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# arduino-cli --build-path ./build 로 빌드한 경우와
# Arduino IDE 기본 출력 경로 두 가지를 모두 지원
BUILD_DIRS = [
    os.path.join(BASE_DIR, "build"),
    os.path.join(BASE_DIR, "build", "esp32.esp32.ttgo-t1"),
]

# TTGO T1 은 CP2102(SLAB/usbserial) 또는 CH340(wchusbserial) 로 잡힌다.
PORT_PATTERNS = [
    "/dev/cu.usbserial*",
    "/dev/cu.SLAB_USBtoUART*",
    "/dev/cu.wchusbserial*",
]
WAIT_TIMEOUT_SEC = 120


def find_build_dir():
    """앱 .bin 이 들어있는 빌드 디렉터리. 없으면 None."""
    for d in BUILD_DIRS:
        if os.path.isfile(os.path.join(d, f"{SKETCH_NAME}.ino.bin")):
            return d
    return None


def find_ports():
    ports = []
    for pattern in PORT_PATTERNS:
        ports.extend(glob.glob(pattern))
    return sorted(ports)


def port_holder(port):
    """포트를 점유 중인 프로세스명. 없으면 None. (IDE 시리얼 모니터/CoolTerm 등)"""
    try:
        result = subprocess.run(["lsof", port], capture_output=True, text=True, timeout=5)
    except Exception:
        return None
    lines = [l for l in result.stdout.splitlines()[1:] if l.strip()]
    return lines[0].split()[0] if lines else None


def pick_port(ports):
    if len(ports) > 1:
        print(f"⚠️  포트가 여러 개 잡혔습니다: {', '.join(ports)}")
        print(f"   첫 번째({ports[0]})로 진행합니다. 다른 보드는 뽑고 다시 실행하세요.")
    return ports[0]


def wait_for_board():
    known = find_ports()
    if known:
        return pick_port(known)

    print(f"🔌 TTGO T1 을 USB 에 꽂아주세요... (최대 {WAIT_TIMEOUT_SEC}초 대기)")
    deadline = time.time() + WAIT_TIMEOUT_SEC
    while time.time() < deadline:
        ports = find_ports()
        if ports:
            time.sleep(1)  # 포트 노드가 안정화될 때까지 잠깐 대기
            return pick_port(find_ports())
        time.sleep(0.5)
    return None


def wait_for_free_port(port):
    """시리얼 모니터가 물고 있으면 놓을 때까지 기다린다."""
    holder = port_holder(port)
    if holder is None:
        return True

    print(f"⛔ {port} 를 '{holder}' 가 점유 중입니다.")
    print("   Arduino IDE 시리얼 모니터나 CoolTerm 을 닫아주세요. (대기 중...)")
    deadline = time.time() + WAIT_TIMEOUT_SEC
    while time.time() < deadline:
        if port_holder(port) is None:
            print("   포트가 해제되었습니다.")
            return True
        time.sleep(1)
    return False


def main():
    build_dir = find_build_dir()
    if build_dir is None:
        print(f"❌ 빌드 결과물이 없습니다: {SKETCH_NAME}.ino.bin")
        print("   먼저 아래를 실행하세요:")
        print(f"   arduino-cli compile --fqbn {FQBN} --build-path build {SKETCH_NAME}.ino")
        return 1

    app_bin = os.path.join(build_dir, f"{SKETCH_NAME}.ino.bin")
    size = os.path.getsize(app_bin)
    mtime = time.strftime("%Y-%m-%d %H:%M", time.localtime(os.path.getmtime(app_bin)))
    print(f"📦 펌웨어: {size:,} bytes (빌드 {mtime})")

    port = wait_for_board()
    if port is None:
        print("❌ 보드를 찾지 못했습니다. USB 케이블과 드라이버(CP2102/CH340)를 확인하세요.")
        return 1

    print(f"🔍 포트 인식: {port}")

    if not wait_for_free_port(port):
        print("❌ 포트가 계속 점유 중입니다. 해당 프로그램을 종료하고 다시 실행하세요.")
        return 1

    print("⚡ 업로드 시작...")

    result = subprocess.run(
        ["arduino-cli", "upload", "--fqbn", FQBN, "-p", port, "--input-dir", build_dir],
        cwd=BASE_DIR,
    )
    if result.returncode != 0:
        print("❌ 업로드 실패.")
        print("   - 전송 도중 끊겼다면 이 파일의 FQBN UploadSpeed 를 115200 으로 낮추세요.")
        print("   - 보드의 BOOT 버튼을 누른 채 다시 시도해 보세요.")
        print("   - GPIO2(MAIN_BEETLE_RX) 배선이 물려 있으면 분리하세요.")
        return result.returncode

    print("✅ 업로드 완료")
    print(f"   시리얼 모니터: arduino-cli monitor -p {port} -c baudrate=115200")
    return 0


if __name__ == "__main__":
    sys.exit(main())
