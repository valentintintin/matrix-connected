#ifndef MATRIX_CONNECTED_APPLETSTATICSYMBOLS_H
#define MATRIX_CONNECTED_APPLETSTATICSYMBOLS_H

#include <CircularBuffer.h>

#include "Engine/Applet.h"
#include "MessageSettings.h"

#define MAX_SYMBOLS 5
#define MAX_LENGTH_SYMBOLS 4

class AppletStaticSymbols : public Applet {

public:
    explicit AppletStaticSymbols(Orchestror *orchestror, const char* name, MD_MAX72XX::fontType_t* font);

    void onResume() override;
    void onPause() override;
    bool shouldBeResumed(bool animationFinished) override;
    void draw(bool animationFinished) override;
    void printSerial() override;

    void addSymbols(const char* symbols, unsigned long secondToCount);
private:
    MD_MAX72XX::fontType_t* font;

    char symbols[MAX_LENGTH_SYMBOLS + 1]{};
    CircularBuffer<MessageShortSettings, MAX_SYMBOLS> messages;
    Timer timer;

    bool hasSymbols = false;

    void popMessage();
};


#endif //MATRIX_CONNECTED_APPLETSTATICSYMBOLS_H
