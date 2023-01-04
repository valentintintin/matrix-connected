#include "AppletCountdown.h"

AppletCountdown::AppletCountdown(Orchestror *orchestror, unsigned long secondToCount, const char* name, bool songAtTheEnd)
    : Applet(orchestror, PSTR("Countdown"), COUNTDOWN, 10),
    songAtTheEnd(songAtTheEnd), timer(secondToCount * 1000) {
    withThirdData = getNumberColumns() > 4 * 8;

    if (name != nullptr) {
        strcpy(this->name, name);

        if (!orchestror->getSystem()->addMessage(this->name)) {
            DPRINTLN(F("Impossible to get applet message"));
        }
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

        millisToString(deltaMillis, timeStr, withThirdData);

        if (strlen(name) > 1 && deltaMillis % MESSAGE_RECALL_MS_SECOND == 0) {
            orchestror->getSystem()->addMessage(name);
        }
    } else {
        stopTimer();
    }
}

void AppletCountdown::draw(bool animationFinished) {
    if (animationFinished) {
        getMatrix()->displayZoneText(getIdZone(), timeStr, PA_CENTER, 0, 25, PA_PRINT, PA_PRINT);
    }
}

void AppletCountdown::printSerial() {
    Applet::printSerial(); DPRINT(F("\tName: ")); DPRINTLN(name); DPRINT(F(", Time: ")); DPRINTLN(timeStr);
}

void AppletCountdown::stopTimer() {
    timer.setExpired();

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

byte AppletCountdown::getPriority() const {
    unsigned long deltaMillis = timer.getTimeLeft();

    if (deltaMillis <= PRIORITY_MAX_BELLOW_MS_SECOND) {
        return 100;
    }

    return Applet::getPriority();
}
