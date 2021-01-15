#include <ESP8266WiFi.h>
#include <NtpClientLib.h>
#include <ESPAsyncWiFiManager.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Engine/WebServer.h>
#include <Applets/AppletMessage.h>
#include <Applets/AppletHeart.h>

#include "Engine/Orchestror.h"
#include "Engine/Utils.h"
#include "Applets/AppletClock.h"
#include "FontData.h"

#define CS_PIN D8
#define LED_PIN D0
#define SOUND_PIN D1
#define AP_SSID "PixelClock"

MD_Parola matrix = MD_Parola(MD_MAX72XX::FC16_HW, CS_PIN, 16);
Orchestror orchestror(&matrix);

WebServer webServer(&matrix, &orchestror);

//void configModeCallback(AsyncWiFiManager *myWiFiManager) {
//    screen.setLed(true);
//    screen.setMainApplet(new AppletMessage(&screen, myWiFiManager->getConfigPortalSSID()));
//    screen.refresh();
//}

void setup() {
    Serial.begin(115200);

    DPRINTLN(F("[PROGRAM]Start"));

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    DPRINTLN(F("[LED]High"));
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_PIN, HIGH);

    DPRINTLN(F("[MATRIX]Start"));
    matrix.begin(3);
    matrix.setZone(0, 0, 9);
    matrix.setZone(1, 10, 14);
    matrix.setZone(2, 15, 15);
    matrix.setIntensity(0);
    matrix.setPause(0);
    matrix.setSpeed(20);
    matrix.setFont(font);

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

    DPRINT(F("[ORCHESTROR]")); DPRINT(NB_MAX_APPLETS); DPRINTLN(F(" applets max"));
    orchestror.addApplet(new AppletHeart(&orchestror, 2));
    orchestror.addApplet(new AppletMessage(&orchestror, 0, String(PSTR(AP_SSID))));
    orchestror.addApplet(new AppletMessage(&orchestror, 0, WiFi.localIP().toString()));
    orchestror.addApplet(new AppletClock(&orchestror, 1, true));

    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_PIN, LOW);
    DPRINTLN(F("[LED]Low"));

    DPRINTLN(F("[PROGRAM]OK"));
}

void loop() {
    orchestror.update();
}
