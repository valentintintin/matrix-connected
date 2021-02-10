#ifndef APPLET_COUNTDOWN_H
#define APPLET_COUNTDOWN_H

#include "Engine/Applet.h"

class AppletCountdown : public Applet {

public:
    AppletCountdown(Orchestror *orchestror, uint64_t secondToCount);

    void stopTimer(bool forced = false);

    bool shouldBePaused(bool isAnimationFinished) override;
    bool shouldBeDestroyed(bool isAnimationFinished) override;
    void refresh() override;
    void draw(MD_Parola *matrix, bool isAnimationFinished) override;
    void printSerial() override;

private:
    bool running;
    uint64_t millisToCount, initTime, lastTime;
    char timeStr[16];
};

#endif
