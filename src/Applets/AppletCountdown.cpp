#include "AppletCountdown.h"

AppletCountdown::AppletCountdown(Orchestror *orchestror, uint64_t secondToCount) : Applet(orchestror, PSTR("Countdown"), 10),
    running(true), stopped(false), millisToCount(secondToCount * 1000), initTime(millis()) {
}

AppletCountdown::~AppletCountdown() = default;

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
            stopTimer();
//            timer.restart();
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
    stopped = true;

    strcpy_P(timeStr, PSTR("Fin !"));
}

void AppletCountdown::resumeTimer() {
    running = true;
    stopped = false;
}

void AppletCountdown::pauseTimer() {
    running = false;
    stopped = false;
}
