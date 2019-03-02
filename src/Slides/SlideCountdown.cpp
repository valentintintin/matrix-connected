#include <Engine/Utils.h>
#include "SlideCountdown.h"

SlideCountdown::SlideCountdown(Screen *screen) : Slide(screen), initTime(millis()) {
    timeString.reserve(15);
    setZone(startX, widthX, _PRINT);
    create();
    restart();
}

SlideCountdown::~SlideCountdown() {
}

void SlideCountdown::start() {
    running = true;
    timer.restart();
}

void SlideCountdown::restart(uint64_t millisToCount) {
    if (millisToCount > 0) {
        this->millisToCount = millisToCount * 1000;
    }
    initTime = millis();
    start();
}

void SlideCountdown::stop() {
    running = false;
    timer.restart();
}

String SlideCountdown::getText() {
    if (running) {
        lastTime = millis();

        if (lastTime - initTime < millisToCount) {
            millisToString(millisToCount - (lastTime - initTime), &timeString);
        } else {
            stop();
            timeString.remove(0, timeString.length());
            timeString.concat("Fin !");
        }
    }

    return timeString;
}

bool SlideCountdown::isFinished() {
    return running ? true : baseIsFinished();
}

bool SlideCountdown::shouldRecreate() {
    return running;
}
