#ifndef SLIDE_CLOCK_H
#define SLIDE_CLOCK_H

#include <NtpClientLib.h>
#include "Engine/Slide.h"
#include "Engine/Timer.h"

const char PROGMEM dong[] = "dong:d=10,o=6,b=180,c,e,g";

const byte PROGMEM hearts[][8] = {
        {
                B00000000,
                B00000000,
                B00101000,
                B01010100,
                B01000100,
                B00101000,
                B00010000,
                B00000000
        },
        {
                B00000000,
                B00000000,
                B00101000,
                B01111100,
                B01111100,
                B00111000,
                B00010000,
                B00000000
        },
        {
                B00000000,
                B01000100,
                B11101110,
                B11010110,
                B11000110,
                B01101100,
                B00111000,
                B00010000
        },
        {
                B00000000,
                B01000100,
                B11101110,
                B11111110,
                B11111110,
                B01111100,
                B00111000,
                B00010000
        }};

class SlideClock : public Slide {

public:
    explicit SlideClock(Screen *screen);

    ~SlideClock();

    String getText() override;

    bool isFinished() override;

    bool shouldRecreate() override;

    void showRaw() override;

private:
    Timer heartTimer;
    byte currentHeart = 0;
};

#endif
