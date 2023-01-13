#include "AppletMessageLoop.h"
#include "../Engine/Utils.h"

AppletMessageLoop::AppletMessageLoop(Orchestror *orchestror, const char* messageToAdd, uint64_t secondToCount) :
    Applet(orchestror, PSTR("MessageLoop"), MESSAGE_LOOP, 20),
    timer(secondToCount * 1000)
{
    strcpy(message, messageToAdd);
    utf8Ascii(message);
}

bool AppletMessageLoop::shouldBeResumed(bool animationFinished) {
    return !timer.hasExpired() || !animationFinished;
}

bool AppletMessageLoop::shouldBeDestroyed(bool animationFinished) {
    return timer.hasExpired();
}

void AppletMessageLoop::draw(bool animationFinished) {
    if (animationFinished) {
        getMatrix()->displayZoneText(getIdZone(), message, PA_CENTER, 25, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    }
}

void AppletMessageLoop::printSerial() {
    Applet::printSerial(); DPRINT(F("\tMessage: ")); DPRINT(message); DPRINT(F(" Duration: ")); DPRINTLN(timer.getTimeLeft());
}

void AppletMessageLoop::stopTimer() {
    timer.setExpired();
}