#ifndef SLIDE_COUTDOWN_H
#define SLIDE_COUTDOWN_H

#include "Engine/Slide.h"

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

private:
    bool running = false;
    uint64_t millisToCount, initTime, lastTime;
    String timeString;
};

#endif
