#include <ESP8266WiFi.h>
#include <NtpClientLib.h>

#include "Engine/Screen.h"
//#include "Engine/WebServer.h"
#include <ESP8266WebServer.h>
#include "Slides/SlideClock.h"
#include "Slides/SlideMessage.h"
#include "Slides/SlideTimer.h"
#include "Slides/SlideCountdown.h"
#include "../../../../../.platformio/packages/toolchain-xtensa/xtensa-lx106-elf/include/c++/4.8.2/cstdint"

byte pinCS = D8; // Attach CS to this pin, DIN to MOSI and CLK to SCK
byte numberOfHorizontalDisplays = 8;

Screen screen(pinCS, numberOfHorizontalDisplays);
SlideClock slideClock(&screen);
SlideTimer slideTimer(&screen);
SlideCountdown slideCountdown(&screen);
//WebServer webServer(&screen);
ESP8266WebServer server(80);

void handleAddMessage() {
    if (server.hasArg(F("msg"))) {
        screen.addSlide(new SlideMessage(&screen, server.arg("msg")));
        server.send(201, F("text/plain"), F("OK"));
    } else {
        server.send(400, F("text/plain"), F("Missing msg parameter in query"));
    }
}

void handleStartTimer() {
    slideTimer.restart();
    screen.setMainSlide(&slideTimer);
    server.send(201, F("text/plain"), F("OK"));
}

void handleRestartTimer() {
    slideTimer.start();
    screen.setMainSlide(&slideTimer);
    server.send(201, F("text/plain"), F("OK"));
}

void handleStopTimer() {
    slideTimer.stop();
    screen.setMainSlide(&slideClock);
    server.send(200, F("text/plain"), F("OK"));
}

void handleStartCountdown() {
    if (server.hasArg(F("duration"))) {
        slideCountdown.restart((uint64_t) server.arg(F("duration")).toInt());
        screen.setMainSlide(&slideCountdown);
        server.send(201, F("text/plain"), F("OK"));
    } else {
        server.send(400, F("text/plain"), F("Missing state parameter in query (on|off)"));
    }
}

void handleRestartCountdown() {
    slideCountdown.start();
    screen.setMainSlide(&slideCountdown);
    server.send(201, F("text/plain"), F("OK"));
}

void handleStopCountdown() {
    slideCountdown.stop();
    screen.setMainSlide(&slideCountdown);
    server.send(200, F("text/plain"), F("OK"));
}

void handleSetState() {
    if (server.hasArg(F("state"))) {
        screen.setState(server.arg(F("state")).equalsIgnoreCase(F("on")));
        server.send(200, F("text/plain"), F("OK"));
    } else {
        server.send(400, F("text/plain"), F("Missing duration parameter in query"));
    }
}

void handleNotFound() {
    server.send(404, F("text/plain"), F("Not found"));
}

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

//  webServer.begin();
    server.on(F("/add_message"), handleAddMessage);
    server.on(F("/start_timer"), handleStartTimer);
    server.on(F("/restart_timer"), handleRestartTimer);
    server.on(F("/stop_timer"), handleStopTimer);
    server.on(F("/set_state"), handleSetState);
    server.on(F("/start_countdown"), handleStartCountdown);
    server.on(F("/restart_countdown"), handleRestartCountdown);
    server.on(F("/stop_countdown"), handleStopCountdown);
    server.begin();
}

void loop() {
    server.handleClient();
    screen.refresh();
}
