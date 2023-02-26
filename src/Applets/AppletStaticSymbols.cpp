#include "AppletStaticSymbols.h"

AppletStaticSymbols::AppletStaticSymbols(Orchestror *orchestror, const char* name, MD_MAX72XX::fontType_t* font) :
Applet(orchestror, name, STATIC_SYMBOLS, 10), font(font), timer(5000) {
    symbols[0] = '\0';
}

bool AppletStaticSymbols::shouldBeResumed(bool animationFinished) {
    return hasSymbols;
}

void AppletStaticSymbols::draw(bool animationFinished) {
    if (animationFinished) {
        if (!messages.isEmpty()) {
            popMessage();
            getMatrix()->displayZoneText(getIdZone(), symbols, PA_CENTER, 0, timer.getTimeLeft(), PA_PRINT, PA_PRINT);
        } else {
            hasSymbols = false;
            symbols[0] = '\0';
        }
    }
}

void AppletStaticSymbols::printSerial() {
    Applet::printSerial(); DPRINT(F(" Symbols: "));

    for (byte i = 0; i < strlen(symbols); i++) {
        DPRINT(symbols[i], DEC); DPRINT(F(" "));
    }

    DPRINT(F(", Nb symbols: ")); DPRINT(messages.size());

    DPRINT(F(" Duration: ")); DPRINT(timer.getTimeLeft());

    DPRINT(F(", Has symbols: ")); DPRINTLN(hasSymbols);
}

void AppletStaticSymbols::addSymbols(const char* symbols, uint64_t durationSeconds) {
    if (messages.isFull()) {
        messages.pop();
    }

    MessageShortSettings messageSettings = {
            {'\0'},
            durationSeconds
    };
    strcpy(messageSettings.message, symbols);

    messages.push(messageSettings);
    hasSymbols = true;
}

void AppletStaticSymbols::popMessage() {
    MessageShortSettings newMessage = messages.pop();
    DPRINT(F("New message: ")); DPRINTLN(newMessage.message); printSerial();

    strcpy(symbols, newMessage.message);
    timer.setInterval(newMessage.durationSeconds * 1000, true);
}

void AppletStaticSymbols::onResume() {
    Applet::onResume();
    getMatrix()->setFont(getIdZone(), font);
    getMatrix()->setCharSpacing(getIdZone(), 0);
}

void AppletStaticSymbols::onPause() {
    Applet::onPause();
    getMatrix()->setCharSpacing(getIdZone(), 1);
}
