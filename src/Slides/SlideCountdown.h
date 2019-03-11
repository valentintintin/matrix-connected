#ifndef SLIDE_COUTDOWN_H
#define SLIDE_COUTDOWN_H

#include "Engine/Slide.h"

const char PROGMEM dangoSong[] = "Dango:d=4,o=5,b=200:4f,4d#,2g#,2g#,2a#,2a#,3c.6,2g#,2d#,4f,4d#,2g#,2g#,2a#,2a#,4c6,4c6,2g#.,4f,4d#,2g#,2g#,2a#,2a#,3c.6,2g#,2d#,4f,4d#,2g#,2g#,4a#,4a#,4g#";

class SlideCountdown : public Slide {

public:
    explicit SlideCountdown(Screen *screen);

    ~SlideCountdown();

    String getText() override;

    bool isFinished() override;

    void start();

    void restart(uint64_t millisToCount = 0);

    void stop();

    bool shouldRecreate() override;

    void showRaw() {};

private:
    bool running = false;
    uint64_t millisToCount, initTime, lastTime;
    String timeString;
};

#endif
