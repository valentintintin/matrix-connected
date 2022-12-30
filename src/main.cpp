#include <ESP8266WiFi.h>
#include <NtpClientLib.h>
#include <ESPAsyncWiFiManager.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#include "Engine/WebServer.h"
#include "Engine/System.h"
#include "Engine/Orchestror.h"
#include "Engine/Utils.h"

#define CS_PIN D8
#define LED_PIN 255
#define SOUND_PIN 255
#define NUM_DEVICES 8

System systemEngine(new MD_Parola(MD_MAX72XX::ICSTATION_HW, CS_PIN, NUM_DEVICES), NUM_DEVICES, true, SOUND_PIN, LED_PIN);
//System systemEngine(new MD_Parola(MD_MAX72XX::FC16_HW, CS_PIN, NUM_DEVICES), NUM_DEVICES, true, SOUND_PIN, LED_PIN, ZONE);

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

    Serial.println(String(PSTR(AP_SSID)) + " " + WiFi.localIP().toString());

    DPRINTLN(F("[NTP]Start"));
    NTP.begin();
    NTP.setTimeZone(1);
    NTP.setDayLight(true);

    systemEngine.addMessage((String(PSTR(AP_SSID)) + " " + WiFi.localIP().toString()).c_str());

    webServer.begin();

    digitalWrite(LED_BUILTIN, HIGH);
    systemEngine.setLed(LOW);
    DPRINTLN(F("[LED]Low"));

    DPRINTLN(F("[PROGRAM]OK"));
}

void loop() {
    systemEngine.update();
}
