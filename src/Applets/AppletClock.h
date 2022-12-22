#ifndef APPLET_CLOCK_H
#define APPLET_CLOCK_H

#include "Engine/Applet.h"

class AppletClock : public Applet {

public:
    explicit AppletClock(Orchestror *orchestror);

    void refresh() override;
    bool shouldBeResumed() override;
    bool shouldBeDestroyed() override;
    void draw(MD_Parola *matrix) override;
    void printSerial() override;

private:
    char timeStr[10]{};
};

#endif
