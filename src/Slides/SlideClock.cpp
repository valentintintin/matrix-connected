#include "SlideClock.h"

SlideClock::SlideClock(Screen *screen, bool heartEnabled, bool dongEnabled) : Slide(screen), heartTimer(Timer(250)),
                                                                              heartEnabled(heartEnabled),
                                                                              dongEnabled(dongEnabled) {
    setZone(startX, widthX, _PRINT);
    create();
}

SlideClock::~SlideClock() {
}

String SlideClock::getText() {
    if (dongEnabled && hour() != 0 && minute() == 0 && second() == 0) {
        if (!hasDong) {
            screen->setSongToPlay(dong);
            screen->setBlink();
            hasDong = true;
        }
    } else {
        hasDong = false;
    }
    return NTP.getTimeStr();
}

bool SlideClock::isFinished() {
    return true;
}

bool SlideClock::shouldRecreate() {
    return true;
}

void SlideClock::showRaw() {
    if (heartEnabled) {
        if (heartTimer.hasExpired()) {
            currentHeart++;
            currentHeart %= 4;
            heartTimer.restart();
        }
        screen->matrix.drawBitmap((int16_t) (screen->matrix.width() - 8 + 1), 0, hearts[currentHeart], 7, 7, HIGH);
    }
}
