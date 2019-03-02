#include <Engine/Utils.h>
#include "SlideTimer.h"

SlideTimer::SlideTimer(Screen *screen) : Slide(screen), initTime(millis()) {
    timeString.reserve(15);
    setZone(startX, widthX, _PRINT);
    create();
    restart();
}

SlideTimer::~SlideTimer() {
}

void SlideTimer::start() {
    running = true;
}

void SlideTimer::restart() {
    initTime = millis();
    start();
}

void SlideTimer::stop() {
    running = false;
}

String SlideTimer::getText() {
    if (running) {
        lastTime = millis();
        millisToString(lastTime - initTime, &timeString);
    }

    return timeString;
}

bool SlideTimer::isFinished() {
    return running ? true : baseIsFinished();
}

bool SlideTimer::shouldRecreate() {
    return true;
}
