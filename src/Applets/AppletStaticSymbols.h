#ifndef MATRIX_CONNECTED_APPLETSTATICSYMBOLS_H
#define MATRIX_CONNECTED_APPLETSTATICSYMBOLS_H

#include "Engine/Applet.h"

class AppletStaticSymbols : public Applet {

public:
    explicit AppletStaticSymbols(Orchestror *orchestror, const char* name, MD_MAX72XX::fontType_t* font);

    void onResume() override;
    bool shouldBeResumed(bool animationFinished) override;
    bool shouldBeDestroyed(bool animationFinished) override;
    void draw(bool animationFinished) override;
    void printSerial() override;

    void changeSymbols(const char* symbols, uint64_t secondToCount);
private:
    MD_MAX72XX::fontType_t* font;

    char symbols[32]{};
    Timer timer;
};


#endif //MATRIX_CONNECTED_APPLETSTATICSYMBOLS_H
