#include "AppletCountdown.h"

AppletCountdown::AppletCountdown(Orchestror *orchestror, uint64_t secondToCount) : Applet(orchestror, PSTR("Countdown"), COUNTDOWN, 10),
    running(true), millisToCount(secondToCount * 1000), initTime(millis()) {
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

        if (lastTime - initTime < millisToCount) {
            millisToString(millisToCount - (lastTime - initTime), timeStr);
        } else {
            stopTimer();
            orchestror->getSystem()->notify();
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
    Applet::printSerial(); DPRINT(F("\tTime: ")); DPRINTLN(timeStr);
}

void AppletCountdown::stopTimer(bool forced) {
    running = false;

    if (!forced) {
        orchestror->getSystem()->addMessage(String("Fin !"));
        orchestror->getSystem()->notify();
    }
}