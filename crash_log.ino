#include <Preferences.h>

static String g_crashLog = "";

void CrashLogSave(const char* tag) {
    Preferences p;
    p.begin("wdt", false);
    p.putString("cp", tag);
    p.end();
}

void CrashLogClear() {
    Preferences p;
    p.begin("wdt", false);
    p.putString("cp", "");
    p.end();
    g_crashLog = "";
}

void CrashLogLoad() {
    Preferences p;
    p.begin("wdt", true);
    g_crashLog = p.getString("cp", "");
    p.end();
    if (g_crashLog.length() > 0)
        Serial.println("[CRASH] last checkpoint: " + g_crashLog);
}

void CrashLogSendIfPending() {
    if (g_crashLog.length() == 0) return;
    if (WiFi.status() != WL_CONNECTED) return;
    has2wifi.Send((String)(const char*)my["device_name"], "crash_log", g_crashLog);
    CrashLogClear();
}
