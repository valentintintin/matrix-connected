#include <ESP8266WiFi.h>
#include <NtpClientLib.h>
#include <ESPAsyncWiFiManager.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include "Engine/WebServer.h"
#include "Engine/System.h"
#include "Engine/Orchestror.h"
#include "Engine/Utils.h"

#define CS_PIN D8
#define LED_PIN D0
#define SOUND_PIN D1
#define AP_SSID "PixelClock"

System systemEngine(new MD_Parola(MD_MAX72XX::FC16_HW, CS_PIN, 16), true, SOUND_PIN, LED_PIN);

WebServer webServer(&systemEngine);

//void configModeCallback(AsyncWiFiManager *myWiFiManager) {
//    screen.setLed(true);
//    screen.setMainApplet(new AppletMessage(&screen, myWiFiManager->getConfigPortalSSID()));
//    screen.refresh();
//}

void setup() {
    Serial.begin(115200);
    randomSeed(analogRead(0));

    DPRINTLN(F("[PROGRAM]Start"));

    pinMode(LED_BUILTIN, OUTPUT);
    DPRINTLN(F("[LED]High"));
    digitalWrite(LED_BUILTIN, LOW);
    systemEngine.setLed(HIGH);

    DPRINTLN(F("[WIFI MANAGER]Start"));
    AsyncWiFiManager wifiManager(&webServer.server, &webServer.dns);
    wifiManager.setDebugOutput(false);
    //wifiManager.setAPCallback(configModeCallback);
    wifiManager.autoConnect(AP_SSID);

    DPRINTLN(F("[NTP]Start"));
    NTP.begin();
    NTP.setTimeZone(1);
    NTP.setDayLight(true);

    webServer.begin();

    Orchestror* orchestror = systemEngine.getOrchestorForZone(ZONE_RIGHT);
//    orchestror->addApplet(new AppletMessage(orchestror, String(PSTR(AP_SSID))));
//    orchestror->addApplet(new AppletMessage(orchestror, WiFi.localIP().toString()));

    digitalWrite(LED_BUILTIN, HIGH);
    systemEngine.setLed(LOW);
    DPRINTLN(F("[LED]Low"));

    DPRINTLN(F("[PROGRAM]OK"));
}

void loop() {
    systemEngine.update();
}
