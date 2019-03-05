#include <ESP8266WiFi.h>
#include <NtpClientLib.h>

#include "Engine/Screen.h"
#include "Engine/WebServer.h"
#include "Slides/SlideClock.h"
#include "Slides/SlideMessage.h"
#include "Slides/SlideTimer.h"
#include "Slides/SlideCountdown.h"

byte pinCS = D8; // Attach CS to this pin, DIN to MOSI and CLK to SCK
byte numberOfHorizontalDisplays = 8;

Screen screen(pinCS, numberOfHorizontalDisplays);
SlideClock slideClock(&screen);
WebServer webServer(&screen);

void setup() {
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

    webServer.begin();
}

void loop() {
    screen.refresh();
}
