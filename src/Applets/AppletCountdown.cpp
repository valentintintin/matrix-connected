#include "AppletCountdown.h"

AppletCountdown::AppletCountdown(Orchestror *orchestror, unsigned long secondToCount, String name, bool songAtTheEnd)
    : Applet(orchestror, PSTR("Countdown"), COUNTDOWN, 10),
    songAtTheEnd(songAtTheEnd), timer(secondToCount * 1000) {
    utf8ascii(name).toCharArray(this->name, name.length() + 1);

    if (!orchestror->getSystem()->addMessage(this->name)) {
        DPRINTLN(F("Impossible to get applet message"));
    }

    orchestror->getSystem()->alert();
}

bool AppletCountdown::shouldBeResumed() {
    return !timer.hasExpired();
}

bool AppletCountdown::shouldBeDestroyed() {
    return timer.hasExpired();
}

void AppletCountdown::refresh() {
    Applet::refresh();

    if (!timer.hasExpired()) {
        unsigned long deltaMillis = timer.getTimeLeft();

        millisToString(deltaMillis, timeStr);

        if (strlen(name) > 1 && deltaMillis % MESSAGE_RECALL_MS_SECOND == 0) {
            orchestror->getSystem()->addMessage(name);
        }
    } else {
        stopTimer();
    }
}

void AppletCountdown::draw(MD_Parola *matrix) {
    matrix->displayZoneText(getIdZone(), timeStr, PA_CENTER, 0, 25,PA_PRINT, PA_PRINT);
}

void AppletCountdown::printSerial() {
    Applet::printSerial(); DPRINT(F("\tName: ")); DPRINTLN(name); DPRINT(F(", Time: ")); DPRINTLN(timeStr);
}

void AppletCountdown::stopTimer(bool forced) {
    if (!forced) {
        if (strlen(name) > 1) {
            buffer[0] = '\0';
            sprintf_P(buffer, PSTR("Fin de %s !"), name);
        } else {
            strcpy_P(buffer, PSTR("Fin !"));
        }
        orchestror->getSystem()->addMessage(buffer);

        if (songAtTheEnd) {
            orchestror->getSystem()->notify();
        }
    }
}
