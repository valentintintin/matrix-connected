#include "Timer.h"
#include <Arduino.h>

Timer::Timer(unsigned long interval, bool hasExpired) : interval(interval) {
    if (hasExpired) {
        setExpired();
    } else {
        restart();
    }
}


Timer::~Timer() {
}

bool Timer::hasExpired() {
    return trigger || millis() - timeLast >= interval;
}

void Timer::restart() {
    trigger = false;
    timeLast = millis();
}

void Timer::setExpired() {
    timeLast = 0;
    trigger = true;
}

unsigned long Timer::getTimeLeft() {
    return hasExpired() ? 0 : timeLast + interval - millis();
}

