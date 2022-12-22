#include "AppletHeart.h"

AppletHeart::AppletHeart(Orchestror *orchestror) : Applet(orchestror, PSTR("Heart"), HEART) {
}

bool AppletHeart::shouldBeResumed() {
    return true;
}

bool AppletHeart::shouldBeDestroyed() {
    return false;
}

void AppletHeart::draw(MD_Parola *matrix) {
    currentHeart++;
    currentHeart %= 4;

    heartStr[0] = currentHeart + 1;

    setIntensity(matrix);

    matrix->displayZoneText(getIdZone(), heartStr, PA_LEFT, 0, HEART_PULSE_MS, PA_PRINT, PA_NO_EFFECT);
}

void AppletHeart::printSerial() {
    Applet::printSerial(); DPRINT(F("\tHeart: ")); DPRINTLN(currentHeart);
}

void AppletHeart::onResume(MD_Parola *matrix) {
    Applet::onResume(matrix);
    matrix->setFont(getIdZone(), hearts);
}

void AppletHeart::setIntensity(MD_Parola *matrix) {
    matrix->setIntensity(getIdZone(), currentHeart % 2 == 0 ? 1 : 3); // Heart filled brighter
}
