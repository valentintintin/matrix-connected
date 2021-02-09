#ifndef APPLET_COUNTDOWN_H
#define APPLET_COUNTDOWN_H

#include "../Engine/Applet.h"
#include "../Engine/Timer.h"

const char PROGMEM dangoSong[] = "Dango:d=4,o=5,b=200:4f,4d#,2g#,2g#,2a#,2a#,3c.6,2g#,2d#,4f,4d#,2g#,2g#,2a#,2a#,4c6,4c6,2g#.,4f,4d#,2g#,2g#,2a#,2a#,3c.6,2g#,2d#,4f,4d#,2g#,2g#,4a#,4a#,4g#";

class AppletCountdown : public Applet {

public:
    explicit AppletCountdown(Orchestror *orchestror, uint64_t millisToCount);
    ~AppletCountdown();

    void pauseTimer();
    void stopTimer();
    void resumeTimer();

    bool shouldBePaused(bool isAnimationFinished) override;
    bool shouldBeDestroyed(bool isAnimationFinished) override;
    void refresh() override;
    void draw(MD_Parola *matrix, bool isAnimationFinished) override;
    void printSerial() override;

private:
    bool running = true, stopped = false;
    uint64_t millisToCount, initTime, lastTime;
    char timeStr[16];
};

#endif
