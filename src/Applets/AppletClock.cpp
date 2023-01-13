#include "AppletClock.h"

#include <NtpClientLib.h>

AppletClock::AppletClock(Orchestror *orchestror) :
    Applet(orchestror, PSTR("Clock"), CLOCK, 10) {
    withSecond = getNumberColumns() > 4 * 8;
}

bool AppletClock::shouldBeResumed(bool animationFinished) {
    return true;
}

bool AppletClock::shouldBeDestroyed(bool animationFinished) {
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

void AppletClock::draw(bool animationFinished) {
    if (animationFinished) {
        getMatrix()->displayZoneText(getIdZone(), timeStr, PA_CENTER, 0, 25, PA_PRINT, PA_PRINT);
    }

    if (!withSecond && getMatrix()->isAnimationAdvanced()) {
        byte secondTen = timeStr[6] - '0';
        byte secondUnit = timeStr[7] - '0';
        bool secondEven = secondUnit % 2 != 0;

        getMatrix()->getGraphicObject()->update(false);

        for (byte y = 1; y <= 5; y++) {
            bool state = secondTen >= y ? !getMatrix()->getInvert() : getMatrix()->getInvert();
            getMatrix()->getGraphicObject()->setPoint(8 - y, getStartColumn(), state);
            getMatrix()->getGraphicObject()->setPoint(8 - y, getEndColumn(), state);
        }

        if (secondEven) {
            if (secondUnit == 5) {
                getMatrix()->getGraphicObject()->setPoint(0, getStartColumn(), !getMatrix()->getInvert());
                getMatrix()->getGraphicObject()->setPoint(0, getEndColumn(), !getMatrix()->getInvert());
            } else {
                bool state = secondUnit > 5 ? !getMatrix()->getInvert() : getMatrix()->getInvert();
                getMatrix()->getGraphicObject()->setPoint(0, getStartColumn(), state);
                getMatrix()->getGraphicObject()->setPoint(0, getEndColumn(), !state);
            }
        }

        getMatrix()->getGraphicObject()->update(true);
    }
}

void AppletClock::printSerial() {
    Applet::printSerial(); DPRINT(F("\tClock: ")); DPRINTLN(timeStr);
}
