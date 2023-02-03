#ifndef MATRIX_CONNECTED_SYSTEM_H
#define MATRIX_CONNECTED_SYSTEM_H

#include <MD_Parola.h>
#include <Ticker.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include "Orchestror.h"
#include "Utils.h"
#include "Timer.h"

#define NB_MAX_ORCHESTROR 1
#define ZONE_MAIN 0
#define INTENSITY 1

#ifdef VALENTIN
#define NB_MAX_ORCHESTROR 3
#define INTENSITY 5
#define ZONE_HEART 1
#define ZONE_CLOCK 2
#elif defined(WILLYAM)
#define NB_MAX_ORCHESTROR 2
#define ZONE_SYMBOL 1
#endif

#define INTERVAL_PING_PIXEL_SERVER (1000 * 60 * 10)

#define MAX_LENGTH_SONG 255
const char PROGMEM dongSong[] = "Dong:d=8,o=6,b=180:c,e,g";
const char PROGMEM alertSong[] = "Alert:d=8,o=5,b=120:c,c#,e,e#,g,g#";
const char PROGMEM dangoSong[] = "Dango:d=4,o=5,b=200:4f,4d#,2g#,2g#,2a#,2a#,3c.6,2g#,2d#,4f,4d#,2g#,2g#,2a#,2a#,4c6,4c6,2g#.,4f,4d#,2g#,2g#,2a#,2a#,3c.6,2g#,2d#,4f,4d#,2g#,2g#,4a#,4a#,4g#";

const char PROGMEM monday[] = "Lundi";
const char PROGMEM tuesday[] = "Mardi";
const char PROGMEM wednesday[] = "Mercredi";
const char PROGMEM thursday[] = "Jeudi";
const char PROGMEM friday[] = "Vendredi";
const char PROGMEM saturday[] = "Samedi";
const char PROGMEM sunday[] = "Dimanche";
const char* const PROGMEM weekDays[] = { sunday, monday, tuesday, wednesday, thursday, friday, saturday };

class System {
public:
    explicit System(MD_Parola *matrix, byte numDevices, bool enableDong = false, byte soundPin = 255, byte ledPin = 255, byte mainZone = 0, bool resetDisplay = false);

    void setMatrixActivated(bool activated);
    void setMatrixIntensity(byte intensity);
    void update();

    bool setSongToPlay(const char *song);
    bool setLed(bool status) const;
    bool setBlink();

    bool notify();
    bool dong();
    bool alert();
    bool showDateMessage();

    bool addMessage(const char* messageToAdd);

    inline bool isMatrixActivated() const {
        return matrixActivated;
    }

    inline byte getMatrixIntensity() const {
        return matrixIntensity;
    }

    inline MD_Parola* getMatrix() {
        return matrix;
    }

    inline Orchestror* getOrchestorForZone(byte idZone) {
        return orchestrors[idZone];
    }

    inline Orchestror* getMainOrchestor() {
        return orchestrors[mainZone];
    }

    void shouldPingPixelServer();

    Applet *getAppletByTypeOnAnyOrchestor(int appletType);

private:
    bool matrixActivated;
    MD_Parola* matrix;

    byte soundPin;
    bool enableDong, hasDong;
    char bufferSong[MAX_LENGTH_SONG], dateStr[64], dayStr[8], pingPixelServerPayload[128];

    byte mainZone;
    bool resetDisplay;

    byte ledPin;
    Ticker* blinkTicker;
    byte blinkCounter;

    byte matrixIntensity;

    Orchestror* orchestrors[NB_MAX_ORCHESTROR];

    WiFiClientSecure wifiClient;
    HTTPClient http;
    Timer timerPingPixelServer;

    void blinkProcess();
    bool pingPixelServer();
};


#endif //MATRIX_CONNECTED_SYSTEM_H
