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
#define RESET_DISPLAY false

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
#define RESET_DISPLAY true
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

MD_Parola parola(MATRIX_TYPE, CS_PIN, NUM_DEVICES);
System systemEngine(&parola, NUM_DEVICES, DONG, SOUND_PIN, LED_PIN, RESET_DISPLAY);

WebServer webServer(&systemEngine);

boolean syncEventTriggered = false; // True if a time even has been triggered
NTPSyncEvent_t ntpEvent; // Last triggered event

//void configModeCallback(AsyncWiFiManager *myWiFiManager) {
//    screen.setLed(true);
//    screen.setMainApplet(new AppletMessage(&screen, myWiFiManager->getConfigPortalSSID()));
//    screen.refresh();
//}

void setup() {
    Serial.begin(115200);
    randomSeed(analogRead(0));

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    systemEngine.setLed(HIGH);

    WiFi.hostname(AP_SSID);

    AsyncWiFiManager wifiManager(&webServer.server, &webServer.dns);
    wifiManager.setDebugOutput(false);
    //wifiManager.setAPCallback(configModeCallback);
    wifiManager.autoConnect(AP_SSID);

    Serial.println(String(PSTR(AP_SSID)) + " " + WiFi.localIP().toString());

    NTP.onNTPSyncEvent ([](NTPSyncEvent_t event) {
        ntpEvent = event;
        syncEventTriggered = true;
    });

    NTP.begin();
    NTP.setNTPTimeout(30000);
    NTP.setTimeZone(1);
    NTP.setDayLight(true);

    webServer.begin();

    digitalWrite(LED_BUILTIN, HIGH);
    systemEngine.setLed(LOW);

    DPRINTLN(F("[PROGRAM]OK"));

#ifndef DEBUG
    char temp[64];
    sprintf_P(temp, PSTR("%s IP: %s V%.2f"), AP_SSID, WiFi.localIP().toString().substring(9).c_str(), VERSION);
    systemEngine.addMessage(temp);
#endif
}

void loop() {
    systemEngine.update();

    if (syncEventTriggered) {
        syncEventTriggered = false;

        if (ntpEvent < 0 && NTP.getLastNTPSync() > 0) {
            DPRINTLN("[NTP] Time Sync error: %d", ntpEvent);
            ESP.restart();
        }
    }
}
