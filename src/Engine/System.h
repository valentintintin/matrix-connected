#ifndef MATRIX_CONNECTED_SYSTEM_H
#define MATRIX_CONNECTED_SYSTEM_H

#include <MD_Parola.h>
#include <Ticker.h>

#include "Orchestror.h"
#include "Utils.h"

#define NB_MAX_ORCHESTROR 1

#define ZONE 0

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
    explicit System(MD_Parola *matrix, bool enableDong = false, byte soundPin = 255, byte ledPin = 255);

    void setMatrixActivated(bool activated);
    void update();

    void setSongToPlay(const char *song);
    void setLed(bool status) const;
    void setBlink();

    void notify();
    void dong();
    void alert();
    void showDateMessage();

    bool addMessage(const String& messageToAdd);
    bool addMessage(const char* messageToAdd);

    inline bool isMatrixActivated() const {
        return matrixActivated;
    }

    inline MD_Parola* getMatrix() {
        return matrix;
    }

    inline Orchestror* getOrchestorForZone(byte idZone) {
        return orchestrors[idZone];
    }

private:
    bool matrixActivated;
    MD_Parola* matrix;

    byte soundPin;
    bool enableDong, hasDong;
    char bufferSong[MAX_LENGTH_SONG], dateStr[64], dayStr[8];

    byte ledPin;
    Ticker* blinkTicker;
    byte blinkCounter;

    Orchestror* orchestrors[NB_MAX_ORCHESTROR];

    void blinkProcess();
};


#endif //MATRIX_CONNECTED_SYSTEM_H
