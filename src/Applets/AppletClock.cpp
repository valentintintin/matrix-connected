#include "AppletClock.h"

#include <NtpClientLib.h>

AppletClock::AppletClock(Orchestror *orchestror) : Applet(orchestror, PSTR("Clock"), CLOCK, 10) {
}

bool AppletClock::shouldBeResumed() {
    return true;
}

bool AppletClock::shouldBeDestroyed() {
    return false;
}

void AppletClock::refresh() {
    NTP.getTimeStr().toCharArray(timeStr, 10);
}

void AppletClock::draw(MD_Parola *matrix) {
    matrix->displayZoneText(getIdZone(), timeStr, PA_CENTER, 0, 25, PA_PRINT, PA_PRINT);
}

void AppletClock::printSerial() {
    Applet::printSerial(); DPRINT(F("\tClock: ")); DPRINTLN(timeStr);
}
