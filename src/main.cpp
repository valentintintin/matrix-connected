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
#define LED_PIN 255
#define SOUND_PIN 255
#define AP_SSID "Horloge Willyam"

System systemEngine(new MD_Parola(MD_MAX72XX::ICSTATION_HW, CS_PIN, 8), false, SOUND_PIN, LED_PIN);

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

    Orchestror* orchestror = systemEngine.getOrchestorForZone(ZONE);
    orchestror->getSystem()->addMessage(String(PSTR(AP_SSID)) + " " + WiFi.localIP().toString());
    DPRINTLN(String(PSTR(AP_SSID)) + " " + WiFi.localIP().toString());

    digitalWrite(LED_BUILTIN, HIGH);
    systemEngine.setLed(LOW);
    DPRINTLN(F("[LED]Low"));

    DPRINTLN(F("[PROGRAM]OK"));
}

void loop() {
    systemEngine.update();

//    Serial.print(F("Heap: ")); Serial.println(ESP.getFreeHeap());
}
