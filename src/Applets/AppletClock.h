#ifndef APPLET_CLOCK_H
#define APPLET_CLOCK_H

#include "../Engine/Applet.h"

class AppletClock : public Applet {

public:
    explicit AppletClock(Orchestror *orchestror);
    ~AppletClock();

    void onResume(MD_Parola* matrix) override;
    bool shouldBePaused(bool isAnimationFinished) override;
    bool shouldBeDestroyed(bool isAnimationFinished) override;
    void draw(MD_Parola *matrix, bool isAnimationFinished) override;
    void printSerial() override;

private:
    char timeStr[10];
};

#endif
