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
#define MATRIX_TYPE MD_MAX72XX::FC16_HW
#define DONG true

#ifdef VALENTIN
#define LED_PIN D0
#define SOUND_PIN D1
#define NUM_DEVICES 16
#define MATRIX_TYPE MD_MAX72XX::FC16_HW
#elif defined(WILLYAM)
#define LED_PIN 255
#define SOUND_PIN 255
#define NUM_DEVICES 8
#define MATRIX_TYPE MD_MAX72XX::ICSTATION_HW
#elif defined(VALENTIN_SMALL)
#define LED_PIN 255
#define SOUND_PIN 255
#define NUM_DEVICES 4
#define MATRIX_TYPE MD_MAX72XX::FC16_HW
#elif defined(VALENTIN_SMALL_STATE)
#define LED_PIN 255
#define SOUND_PIN 255
#define NUM_DEVICES 2
#define MATRIX_TYPE MD_MAX72XX::GENERIC_HW
#define DONG false
#endif

System systemEngine(new MD_Parola(MATRIX_TYPE, CS_PIN, NUM_DEVICES), NUM_DEVICES, DONG, SOUND_PIN, LED_PIN);

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

    webServer.begin();

    digitalWrite(LED_BUILTIN, HIGH);
    systemEngine.setLed(LOW);
    DPRINTLN(F("[LED]Low"));

    DPRINTLN(F("[PROGRAM]OK"));

#ifndef DEBUG
    systemEngine.addMessage((String(PSTR(AP_SSID)) + " " + WiFi.localIP().toString()).c_str());
#endif
}

void loop() {
    systemEngine.update();
}
