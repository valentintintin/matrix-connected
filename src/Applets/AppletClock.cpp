#include "AppletClock.h"

#include <NtpClientLib.h>

AppletClock::AppletClock(Orchestror *orchestror) : Applet(orchestror, PSTR("Clock"), CLOCK) {
}

bool AppletClock::shouldBePaused(bool isAnimationFinished) {
    return false;
}

bool AppletClock::shouldBeDestroyed(bool isAnimationFinished) {
    return false;
}

void AppletClock::draw(MD_Parola *matrix, bool isAnimationFinished) {
    if (isAnimationFinished) {
        NTP.getTimeStr().toCharArray(timeStr, 10);

        matrix->displayReset(getIdZone());
    }
}

void AppletClock::printSerial() {
    Applet::printSerial(); DPRINT(F("\tClock: ")); DPRINTLN(timeStr);
}

void AppletClock::onResume(MD_Parola* matrix) {
    Applet::onResume(matrix);

    matrix->displayZoneText(getIdZone(), timeStr, PA_LEFT, 0, 200,PA_PRINT, PA_NO_EFFECT);
}