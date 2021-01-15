#include "AppletCountdown.h"

AppletCountdown::AppletCountdown(Orchestror* orchestror, byte idZone, uint64_t millisToCount) : Applet(orchestror, idZone, PSTR("Countdown"), 10) {
}

AppletCountdown::~AppletCountdown() {
}

bool AppletCountdown::shouldBePaused(bool isAnimationFinished) {
    return !running;
}

bool AppletCountdown::shouldBeDestroyed(bool isAnimationFinished) {
    return stopped;
}

void AppletCountdown::refresh() {
    Applet::refresh();

    if (running) {
        lastTime = millis();

        if (lastTime - initTime < millisToCount) {
            millisToString(millisToCount - (lastTime - initTime), timeStr);
        } else {
//            stop();
//            timer.restart();
                strcpy_P(timeStr, PSTR("Fin !"));
//            screen->setSongToPlay(dangoSong);
//            screen->setBlink();
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

void AppletCountdown::stopTimer() {
    running = false;
}

void AppletCountdown::resumeTimer() {
    running = true;
}

void AppletCountdown::pauseTimer() {
    running = false;
}
