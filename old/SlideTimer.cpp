#include <Engine/Utils.h>
#include "AppletTimer.h"

AppletTimer::AppletTimer(Screen *screen) : Applet(screen), initTime(millis()) {
    timeString.reserve(15);
    setZone(startX, widthX, _PRINT);
    create();
    restart();
}

AppletTimer::~AppletTimer() {
}

void AppletTimer::start() {
    running = true;
}

void AppletTimer::restart() {
    initTime = millis();
    start();
}

void AppletTimer::stop() {
    running = false;
}

String AppletTimer::getText() {
    if (running) {
        lastTime = millis();
        millisToString(lastTime - initTime, &timeString);
    }

    return timeString;
}

bool AppletTimer::isFinished() {
    return running ? true : baseIsFinished();
}

bool AppletTimer::shouldRecreate() {
    return true;
}
