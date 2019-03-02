#include "SlideClock.h"

SlideClock::SlideClock(Screen *screen, bool withSeconds) : Slide(screen), withSeconds(withSeconds) {
    if (withSeconds) {
        setZone(startX, widthX, _PRINT);
    } else {
        setZone(startX, widthX >> 1, _PRINT);
    }
    create();
}

SlideClock::~SlideClock() {
}

String SlideClock::getText() {
    if (withSeconds) {
        return NTP.getTimeStr();
    } else {
        return getTimeStrSimple(NTP.getTime());
    }
}

String SlideClock::getTimeStrSimple(time_t moment) {
    char timeStr[7];
    sprintf(timeStr, "%02d:%02d", hour(moment), minute(moment));
    return timeStr;
}

bool SlideClock::isFinished() {
    return true;
}

bool SlideClock::shouldRecreate() {
    return true;
}
