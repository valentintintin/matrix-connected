#include <Engine/Utils.h>
#include "AppletCountdown.h"

AppletCountdown::AppletCountdown(Screen *screen) : Applet(screen), initTime(millis()) {
    timeString.reserve(15);
    setZone(startX, widthX, _PRINT);
    create();
    restart();
}

AppletCountdown::~AppletCountdown() {
}

void AppletCountdown::start() {
    running = true;
    timer.restart();
}

void AppletCountdown::restart(uint64_t millisToCount) {
    if (millisToCount > 0) {
        this->millisToCount = millisToCount * 1000;
    }
    initTime = millis();
    start();
}

void AppletCountdown::stop() {
    running = false;
}

String AppletCountdown::getText() {
    if (running) {
        lastTime = millis();

        if (lastTime - initTime < millisToCount) {
            millisToString(millisToCount - (lastTime - initTime), &timeString);
        } else {
            stop();
            timer.restart();
            timeString.remove(0, timeString.length());
            timeString.concat("Fin !");
            screen->setSongToPlay(dangoSong);
            screen->setBlink();
        }
    }

    return timeString;
}

bool AppletCountdown::isFinished() {
    return running ? true : baseIsFinished();
}

bool AppletCountdown::shouldRecreate() {
    return running;
}
