#ifndef SLIDE_TIMER_H
#define SLIDE_TIMER_H

#include "Engine/Slide.h"

class SlideTimer : public Slide {

public:
    explicit SlideTimer(Screen *screen);

    ~SlideTimer();

    String getText() override;

    bool isFinished() override;

    void start();

    bool shouldRecreate() override;

    void restart();

    void stop();

    void showRaw() {};

private:
    bool running = false;
    uint64_t initTime, lastTime;
    String timeString;
};

#endif
