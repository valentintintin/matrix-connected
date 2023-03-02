#include "Timer.h"
#include <Arduino.h>

Timer::Timer(unsigned long interval, bool hasExpired) : interval(interval) {
    if (hasExpired) {
        setExpired();
    } else {
        restart();
    }
}

bool Timer::hasExpired() const {
    if (isPaused()) {
        return false;
    }

    return trigger || millis() - timeLast >= interval;
}

void Timer::setInterval(unsigned long newInterval, bool shouldRestart) {
    interval = newInterval;

    if (shouldRestart) {
        restart();
    }
}

void Timer::restart() {
    trigger = false;
    timeLast = millis();
    timePause = 0;
}

void Timer::setExpired() {
    timeLast = 0;
    trigger = true;
    timePause = 0;
}

unsigned long Timer::getTimeLeft() const {
    if (isPaused()) {
//        Serial.print(F("TimeLast: ")); Serial.print(timeLast); Serial.print(F(" TimePause: ")); Serial.print(timePause); Serial.print(F(" millis: ")); Serial.print(millis()); Serial.print(F(" interval: ")); Serial.println(interval);
        return interval - (timePause - timeLast);
    }

    return hasExpired() ? 0 : timeLast + interval - millis();
}

void Timer::pause() {
    if (isPaused() || getTimeLeft() <= 1) {
        return;
    }

    timePause = millis();
}

void Timer::resume() {
    if (!isPaused()) {
        return;
    }

    setInterval(getTimeLeft());
}

