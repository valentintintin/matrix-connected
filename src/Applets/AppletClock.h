#ifndef APPLET_CLOCK_H
#define APPLET_CLOCK_H

#include "../Engine/Applet.h"
#include "../Engine/Timer.h"

const char PROGMEM dong[] = "dong:d=10,o=6,b=180,c,e,g";

class AppletClock : public Applet {

public:
    explicit AppletClock(Orchestror* orchestror, byte idZone, bool dongEnabled = false);
    ~AppletClock();

    bool shouldBePaused(bool isAnimationFinished) override;
    bool shouldBeDestroyed(bool isAnimationFinished) override;
    void refresh() override;
    void draw(MD_Parola *matrix, bool isAnimationFinished) override;
    void printSerial() override;

private:
    Timer secondTimer;
    bool hasDong = false;
    bool dongEnabled = false;
    char timeStr[10];
};

#endif
