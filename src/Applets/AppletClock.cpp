#include "AppletClock.h"

#include <NtpClientLib.h>

AppletClock::AppletClock(Orchestror *orchestror, bool withSecond) :
    Applet(orchestror, PSTR("Clock"), CLOCK, 10), withSecond(withSecond) {
}

bool AppletClock::shouldBeResumed() {
    return true;
}

bool AppletClock::shouldBeDestroyed() {
    return false;
}

void AppletClock::refresh() {
    Applet::refresh();

    NTP.getTimeStr().toCharArray(timeStr, sizeof(timeStr));

    if (!withSecond) {
        timeStr[5] = '\0';
        timeStr[2] = timeStr[7] % 2 == 0 ? ':' : ' ';
    }
}

void AppletClock::draw(MD_Parola *matrix) {
    matrix->displayZoneText(getIdZone(), timeStr, PA_CENTER, 0, 25, PA_PRINT, PA_PRINT);
}

void AppletClock::printSerial() {
    Applet::printSerial(); DPRINT(F("\tClock: ")); DPRINTLN(timeStr);
}
