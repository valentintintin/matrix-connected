#ifndef APPLET_SYMBOLS_ANIMATED_H
#define APPLET_SYMBOLS_ANIMATED_H

#include "../Engine/Applet.h"

#define MAX_SYMBOLS 16

typedef struct SymbolSettings {
    unsigned int pause;
    byte intensity;
} SymbolSettings;

typedef struct SymbolAnaimationSettings {
    MD_MAX72XX::fontType_t* font;
    byte nbSymbols;
    SymbolSettings symbolsSettings[MAX_SYMBOLS];
} SymbolAnimationSettings;

class AppletSymbolsAnimated : public Applet {

public:
    explicit AppletSymbolsAnimated(Orchestror *orchestror, const char* name, const SymbolAnimationSettings symbolsAnimationSettings);

    void onResume() override;
    bool shouldBeResumed() override;
    bool shouldBeDestroyed() override;
    void draw(bool animationFinished) override;
    void printSerial() override;

private:
    const SymbolAnimationSettings symbolsAnimationSettings;

    char symbolStr[2]{};
    byte currentSymbol = 0;
};

#endif
