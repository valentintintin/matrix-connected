#include "AppletStaticSymbols.h"

AppletStaticSymbols::AppletStaticSymbols(Orchestror *orchestror, const char* name, MD_MAX72XX::fontType_t* font) :
Applet(orchestror, name, STATIC_SYMBOLS, 10), font(font), timer(5000) {
    symbols[0] = '\0';
}

bool AppletStaticSymbols::shouldBeResumed(bool animationFinished) {
    return !timer.hasExpired();
}

bool AppletStaticSymbols::shouldBeDestroyed(bool animationFinished) {
    return false;
}

void AppletStaticSymbols::draw(bool animationFinished) {
    if (animationFinished) {
        getMatrix()->displayZoneText(getIdZone(), symbols, PA_LEFT, 0, timer.getTimeLeft(), PA_PRINT, PA_PRINT);
    }
}

void AppletStaticSymbols::printSerial() {
    Applet::printSerial(); DPRINT(F(" Symbols: "));

    for (byte i = 0; i < strlen(symbols); i++) {
        DPRINT(symbols[i], DEC); DPRINT(F(" "));
    }

    DPRINT(F(" Duration: ")); DPRINTLN(timer.getTimeLeft());
}

void AppletStaticSymbols::changeSymbols(const char *symbols, uint64_t secondToCount) {
//    for (byte i = 0; i < strlen(symbols); i++) {
//        this->symbols[i] = symbols[i] - '!';
//        this->symbols[i + 1] = '\0';
//    }
    strcpy(this->symbols, symbols);
    timer.setInterval(secondToCount * 1000, true);
}

void AppletStaticSymbols::onResume() {
    Applet::onResume();
    getMatrix()->setFont(getIdZone(), font);
    getMatrix()->setCharSpacing(getIdZone(), 0);
}
