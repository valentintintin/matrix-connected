#include "AppletCountdown.h"

AppletCountdown::AppletCountdown(Orchestror *orchestror, uint64_t secondToCount, String name, bool songAtTheEnd)
: Applet(orchestror, PSTR("Countdown"), COUNTDOWN, 10),
running(true), millisToCount(secondToCount * 1000), songAtTheEnd(songAtTheEnd), initTime(millis()) {
    utf8ascii(name).toCharArray(this->name, name.length() + 1);

    if (!orchestror->getSystem()->addMessage(this->name)) {
        DPRINTLN(F("Impossible to get applet message"));
    }

    orchestror->getSystem()->alert();
}

bool AppletCountdown::shouldBePaused(bool isAnimationFinished) {
    return !running;
}

bool AppletCountdown::shouldBeDestroyed(bool isAnimationFinished) {
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

void AppletCountdown::draw(MD_Parola *matrix, bool isAnimationFinished) {
    if (isAnimationFinished) {
        matrix->displayReset(getIdZone());
        matrix->displayZoneText(getIdZone(), timeStr, PA_LEFT, matrix->getSpeed(), 0,PA_PRINT, PA_NO_EFFECT);
    }
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
            sprintf_P(buffer, PSTR("Fin !"));
        }
        orchestror->getSystem()->addMessage(buffer);

        if (songAtTheEnd) {
            orchestror->getSystem()->notify();
        }
    }
}
