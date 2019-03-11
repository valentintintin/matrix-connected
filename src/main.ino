#include <ESP8266WiFi.h>
#include <NtpClientLib.h>

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

Screen screen(CS_PIN, NUMBER_DISPLAY_X, SOUND_PIN, LED_PIN);
SlideClock slideClock(&screen);
WebServer webServer(&screen);

void setup() {
    screen.setLed(true);
    Serial.begin(115200);
    Serial.println(F("Starting..."));

    WiFi.mode(WIFI_STA);
    WiFi.begin("PixelBox", "***REMOVED***");

    while (WiFi.status() != WL_CONNECTED) { delay(500); }

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
