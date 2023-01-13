#include "AppletSymbolsAnimated.h"

AppletSymbolsAnimated::AppletSymbolsAnimated(Orchestror *orchestror,
 const char *name, SymbolAnimationSettings symbolsAnimationSettings):
        Applet(orchestror, name, SYMBOLS_ANIMATED), symbolsAnimationSettings(symbolsAnimationSettings) {
}

bool AppletSymbolsAnimated::shouldBeResumed(bool animationFinished) {
    return true;
}

bool AppletSymbolsAnimated::shouldBeDestroyed(bool animationFinished) {
    return false;
}

void AppletSymbolsAnimated::draw(bool animationFinished) {
    if (animationFinished) {
        currentSymbol++;
        currentSymbol %= symbolsAnimationSettings.nbSymbols;

        symbolStr[0] = currentSymbol + 1; // because font char 0 is null
        symbolStr[1] = '\0';

        SymbolSettings settings = symbolsAnimationSettings.symbolsSettings[currentSymbol];

        getMatrix()->setIntensity(getIdZone(), settings.intensity);
        getMatrix()->displayZoneText(getIdZone(), symbolStr, PA_CENTER, 0, settings.pause, PA_PRINT, PA_PRINT);
    }
}

void AppletSymbolsAnimated::printSerial() {
    Applet::printSerial(); DPRINT(F("\tCurrent symbol: ")); DPRINTLN(currentSymbol);
}

void AppletSymbolsAnimated::onResume() {
    Applet::onResume();
    getMatrix()->setFont(getIdZone(), symbolsAnimationSettings.font);
}