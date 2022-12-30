#include "AppletMessageLoop.h"

AppletMessageLoop::AppletMessageLoop(Orchestror *orchestror, const char* messageToAdd, uint64_t secondToCount) :
    Applet(orchestror, PSTR("MessageLoop"), MESSAGE_LOOP, 20),
    timer(secondToCount * 1000)
{
    strcpy(message, messageToAdd);
}

bool AppletMessageLoop::shouldBeResumed() {
    return !timer.hasExpired();
}

bool AppletMessageLoop::shouldBeDestroyed() {
    return timer.hasExpired();
}

void AppletMessageLoop::draw(MD_Parola *matrix) {
    matrix->displayZoneText(getIdZone(), message, PA_LEFT, 25, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void AppletMessageLoop::printSerial() {
    Applet::printSerial(); DPRINT(F("\tMessage: ")); DPRINT(message); DPRINT(F(" Duration: ")); DPRINTLN(timer.getTimeLeft());
}

void AppletMessageLoop::stopTimer() {
    timer.setExpired();
}