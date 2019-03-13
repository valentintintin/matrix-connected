#include <ESP8266WiFi.h>
#include <NtpClientLib.h>
#include <ESPAsyncWiFiManager.h>

#include "Engine/Screen.h"
#include "Engine/WebServer.h"
#include "Slides/SlideClock.h"
#include "Slides/SlideMessage.h"
#include "Slides/SlideTimer.h"
#include "Slides/SlideCountdown.h"

#define CS_PIN D8
#define LED_PIN D0
#define SOUND_PIN D1
#define NUMBER_DISPLAY_X 8
#define AP_SSID "PixelClock"

Screen screen(CS_PIN, NUMBER_DISPLAY_X, SOUND_PIN, LED_PIN);
SlideClock slideClock(&screen, true, true);
WebServer webServer(&screen);

void configModeCallback(AsyncWiFiManager *myWiFiManager) {
    screen.setLed(true);
    screen.setMainSlide(new SlideMessage(&screen, myWiFiManager->getConfigPortalSSID()));
    screen.refresh();
}

void setup() {
    Serial.begin(115200);

    AsyncWiFiManager wifiManager(&webServer.server, &webServer.dns);
    wifiManager.setDebugOutput(false);
    wifiManager.setAPCallback(configModeCallback);
    wifiManager.autoConnect(AP_SSID);

    NTP.begin();
    NTP.setTimeZone(1);
    NTP.setDayLight(true);

    screen.setFallBackSlide(&slideClock);
    screen.addSlide(new SlideMessage(&screen, WiFi.localIP().toString()));
    screen.setLed(false);

    webServer.begin();
}

void loop() {
    screen.refresh();
}
