#include "AppletHeart.h"

AppletHeart::AppletHeart(Orchestror* orchestror, byte idZone) : Applet(orchestror, idZone, PSTR("Heart")),
    heartTimer(Timer(HEART_PULSE_MS)) {
}

AppletHeart::~AppletHeart() {
}

bool AppletHeart::shouldBePaused(bool isAnimationFinished) {
    return false;
}

bool AppletHeart::shouldBeDestroyed(bool isAnimationFinished) {
    return false;
}

void AppletHeart::refresh() {
    Applet::refresh();

    if (heartTimer.hasExpired()) {
        currentHeart++;
        currentHeart %= 4;
        heartTimer.restart();
    }

    heartStr[0] = currentHeart + 1;
}

void AppletHeart::draw(MD_Parola *matrix, bool isAnimationFinished) {
    if (isAnimationFinished) {
        matrix->setFont(getIdZone(), hearts);
        matrix->displayReset(getIdZone());
        matrix->displayZoneText(getIdZone(), heartStr, PA_LEFT, matrix->getSpeed(), 0, PA_NO_EFFECT, PA_NO_EFFECT);
    }
}

void AppletHeart::printSerial() {
    Applet::printSerial(); DPRINT(F("\tHeart: ")); DPRINTLN(currentHeart);
}
