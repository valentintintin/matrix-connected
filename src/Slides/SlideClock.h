#ifndef SLIDE_CLOCK_H
#define SLIDE_CLOCK_H

#include <NtpClientLib.h>
#include "Engine/Slide.h"

class SlideClock : public Slide {

public:
    explicit SlideClock(Screen *screen, bool withSeconds = true);

    ~SlideClock();

    String getText() override;

    bool isFinished() override;

    bool shouldRecreate() override;

private:
    String getTimeStrSimple(time_t moment);

    bool withSeconds;
};

#endif
