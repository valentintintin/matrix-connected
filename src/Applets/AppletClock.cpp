#include "AppletClock.h"

#include <NtpClientLib.h>

AppletClock::AppletClock(Orchestror* orchestror, byte idZone, bool dongEnabled) : Applet(orchestror, idZone, PSTR("Clock")),
    secondTimer(Timer(1000, true)), dongEnabled(dongEnabled) {
}
AppletClock::~AppletClock() {
}

bool AppletClock::shouldBePaused(bool isAnimationFinished) {
    return false;
}

bool AppletClock::shouldBeDestroyed(bool isAnimationFinished) {
    return false;
}

void AppletClock::refresh() {
    Applet::refresh();

//    if (dongEnabled && hour() != 0 && minute() == 0 && second() == 0) {
//        if (!hasDong) {
//            screen->setSongToPlay(dong);
//            screen->setBlink();
//            hasDong = true;
//        }
//    } else {
//        hasDong = false;
//    }

    NTP.getTimeStr().toCharArray(timeStr, 10);
}

void AppletClock::draw(MD_Parola *matrix, bool isAnimationFinished) {
    if (isAnimationFinished && secondTimer.hasExpired()) {
        secondTimer.restart();

        matrix->displayReset(getIdZone());
        matrix->displayZoneText(getIdZone(), timeStr, PA_LEFT, matrix->getSpeed(), 0,PA_PRINT, PA_NO_EFFECT);
    }
}

void AppletClock::printSerial() {
    Applet::printSerial(); DPRINT(F("\tClock: ")); DPRINTLN(timeStr);
}
