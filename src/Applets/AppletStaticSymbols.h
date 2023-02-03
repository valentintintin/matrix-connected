#ifndef MATRIX_CONNECTED_APPLETSTATICSYMBOLS_H
#define MATRIX_CONNECTED_APPLETSTATICSYMBOLS_H

#include <ArduinoQueue.h>

#include "Engine/Applet.h"
#include "MessageSettings.h"

#define MAX_MESSAGES 10
#define MAX_LENGTH_MESSAGE 4

class AppletStaticSymbols : public Applet {

public:
    explicit AppletStaticSymbols(Orchestror *orchestror, const char* name, MD_MAX72XX::fontType_t* font);

    void onResume() override;
    void onPause() override;
    bool shouldBeResumed(bool animationFinished) override;
    void draw(bool animationFinished) override;
    void printSerial() override;

    bool addSymbols(const char* symbols, uint64_t secondToCount);
private:
    MD_MAX72XX::fontType_t* font;

    char symbols[MAX_LENGTH_MESSAGE + 1]{};
    ArduinoQueue<MessageSettings> messages = ArduinoQueue<MessageSettings>(MAX_MESSAGES);
    Timer timer;

    bool hasSymbols = false;

    void popMessage();
};


#endif //MATRIX_CONNECTED_APPLETSTATICSYMBOLS_H
