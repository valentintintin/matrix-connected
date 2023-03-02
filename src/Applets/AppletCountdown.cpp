#include "AppletCountdown.h"

AppletCountdown::AppletCountdown(Orchestror *orchestror)
    : Applet(orchestror, PSTR("Countdown"), COUNTDOWN, 10) {
    withThirdData = getNumberColumns() > 4 * 8;
}

bool AppletCountdown::shouldBeResumed(bool animationFinished) {
    return isRunning;
}

void AppletCountdown::refresh() {
    Applet::refresh();

    if (!timer.hasExpired()) {
        unsigned long deltaMillis = timer.getTimeLeft();

        millisToString(deltaMillis, timeStr, withThirdData);

        if (timer.isPaused()) {
            sprintf_P(buffer, PSTR("P %s"), timeStr);
            strcpy(timeStr, buffer);
        }

        if (strlen(name) > 1 && deltaMillis % MESSAGE_RECALL_MS_SECOND == 0) {
            orchestror->getSystem()->addMessage(name);
        }
    } else if (isRunning) {
        stopTimer();
    }
}

void AppletCountdown::draw(bool animationFinished) {
    if (animationFinished) {
        getMatrix()->displayZoneText(getIdZone(), timeStr, PA_CENTER, 0, 25, PA_PRINT, PA_PRINT);
    }
}

void AppletCountdown::printSerial() {
    Applet::printSerial(); DPRINT(F("\tName: ")); DPRINT(name); DPRINT(F(", Time: ")); DPRINTLN(timeStr);
}

void AppletCountdown::startTimer(unsigned long secondToCount, const char *name) {
    if (name != nullptr) {
        if (strlen(name) >= MAX_LENGTH_MESSAGE - 1) {
            Serial.print(F("Message countdown too long: ")); Serial.println(strlen(name));
        } else {
            sprintf_P(buffer, PSTR("Lancement du décompte %s !"), name);
            strcpy(this->name, name);

            if (secondToCount * 1000 < PRIORITY_MAX_BELLOW_MS_SECOND || !orchestror->getSystem()->addMessage(buffer)) {
                DPRINTLN(F("Impossible to add countdown message start"));
            }
        }
    }

    timer.setInterval(secondToCount * 1000, true);
    isRunning = true;

    orchestror->getSystem()->alert();
}


void AppletCountdown::stopTimer(bool withEnd) {
    isRunning = false;
    timer.setExpired();

    if (withEnd) {
        sprintf_P(buffer, PSTR("Fin du décompte %s !"), name);

        if (!orchestror->getSystem()->addMessage(buffer)) {
            DPRINTLN(F("Impossible to add countdown message end"));
        }

        orchestror->getSystem()->notify();
    }
}

byte AppletCountdown::getPriority() const {
    unsigned long deltaMillis = timer.getTimeLeft();

    if (deltaMillis <= PRIORITY_MAX_BELLOW_MS_SECOND) {
        return 100;
    }

    return Applet::getPriority();
}