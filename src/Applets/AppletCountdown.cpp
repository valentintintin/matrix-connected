#include "AppletCountdown.h"

AppletCountdown::AppletCountdown(Orchestror *orchestror, uint64_t secondToCount, String name, bool songAtTheEnd)
: Applet(orchestror, PSTR("Countdown"), COUNTDOWN, 10),
running(true), songAtTheEnd(songAtTheEnd), millisToCount(secondToCount * 1000), initTime(millis()) {
    utf8ascii(name).toCharArray(this->name, name.length() + 1);

    if (!orchestror->getSystem()->addMessage(this->name)) {
        DPRINTLN(F("Impossible to get applet message"));
    }

    orchestror->getSystem()->alert();
}

bool AppletCountdown::shouldBeResumed() {
    return running;
}

bool AppletCountdown::shouldBeDestroyed() {
    return !running;
}

void AppletCountdown::refresh() {
    Applet::refresh();

    if (running) {
        lastTime = millis();

        uint64_t deltaMillis = lastTime - initTime;

        if (deltaMillis < millisToCount) {
            deltaMillis = millisToCount - deltaMillis;

            millisToString(deltaMillis, timeStr);

            if (strlen(name) > 1 && deltaMillis % MESSAGE_RECALL_MS_SECOND == 0) {
                orchestror->getSystem()->addMessage(name);
            }
        } else {
            stopTimer();
        }
    }
}

void AppletCountdown::draw(MD_Parola *matrix) {
    matrix->displayZoneText(getIdZone(), timeStr, PA_CENTER, 0, 25,PA_PRINT, PA_PRINT);
}

void AppletCountdown::printSerial() {
    Applet::printSerial(); DPRINT(F("\tName: ")); DPRINTLN(name); DPRINT(F(", Time: ")); DPRINTLN(timeStr);
}

void AppletCountdown::stopTimer(bool forced) {
    running = false;

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
