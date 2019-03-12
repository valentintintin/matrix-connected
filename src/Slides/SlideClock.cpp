#include "SlideClock.h"

SlideClock::SlideClock(Screen *screen) : Slide(screen), heartTimer(Timer(250)) {
    setZone(startX, widthX, _PRINT);
    create();
}

SlideClock::~SlideClock() {
}

String SlideClock::getText() {
    if (minute() == 0 && second() == 0 && !rtttl::isPlaying()) {
        screen->setSongToPlay(dong);
        screen->setBlink();
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
    if (heartTimer.hasExpired()) {
        currentHeart++;
        currentHeart %= 4;
        heartTimer.restart();
    }
    screen->matrix.drawBitmap(screen->matrix.width() - 8 + 1, 0, hearts[currentHeart], 7, 7, HIGH);
}
