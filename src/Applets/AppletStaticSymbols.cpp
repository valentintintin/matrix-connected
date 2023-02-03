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
        }
    }
}

void AppletStaticSymbols::printSerial() {
    Applet::printSerial(); DPRINT(F(" Symbols: "));

    for (byte i = 0; i < strlen(symbols); i++) {
        DPRINT(symbols[i], DEC); DPRINT(F(" "));
    }

    DPRINT(F(", Nb symbols: ")); DPRINT(messages.itemCount());

    DPRINT(F(" Duration: ")); DPRINT(timer.getTimeLeft());

    DPRINT(F(", Has symbols: ")); DPRINTLN(hasSymbols);
}

bool AppletStaticSymbols::addSymbols(const char* symbols, uint64_t durationSeconds) {
    if (!messages.isFull()) {
        char* symbolsToShow = (char*)malloc ((strlen(symbols) + 1) * sizeof(char));
        strcpy(symbolsToShow, symbols);

//        for (byte i = 0; i < strlen(symbols); i++) {
//            this->symbols[i] = symbols[i] - '!';
//            this->symbols[i + 1] = '\0';
//        }

        MessageSettings messageSettings = {
                symbolsToShow,
                durationSeconds
        };

        messages.enqueue(messageSettings);
        hasSymbols = true;

        return true;
    } else {
        DPRINTLN(F("Too much symbols, leave it !"));
        return false;
    }
}

void AppletStaticSymbols::popMessage() {
    MessageSettings newMessage = messages.dequeue();
    DPRINT(F("New message: ")); DPRINTLN(newMessage.message); printSerial();

    strcpy(symbols, newMessage.message);
    timer.setInterval(newMessage.durationSeconds * 1000, true);

    delete newMessage.message;
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
