#include "AppletClock.h"

#include <NtpClientLib.h>

AppletClock::AppletClock(byte idZone, bool heartEnabled, bool dongEnabled) : Applet(idZone, PSTR("Clock")),
    heartTimer(Timer(250)), secondTimer(Timer(1000, true)), heartEnabled(heartEnabled), dongEnabled(dongEnabled) {
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

//    if (heartEnabled) {
//        if (heartTimer.hasExpired()) {
//            currentHeart++;
//            currentHeart %= 4;
//            heartTimer.restart();
//        }
//            screen->matrix.drawBitmap((int16_t) (screen->matrix.width() - 8 + 1), 0, hearts[currentHeart], 7, 7, HIGH);
//    }
}

void AppletClock::printSerial() {
    Applet::printSerial(); DPRINT(F("\tClock: ")); DPRINTLN(timeStr);
}
