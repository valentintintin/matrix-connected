#ifndef APPLET_CLOCK_H
#define APPLET_CLOCK_H

#include "../Engine/Applet.h"
#include "../Engine/Timer.h"

const char PROGMEM dong[] = "dong:d=10,o=6,b=180,c,e,g";

const byte PROGMEM hearts[][7] = {
    {
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
            B00101000,
            B01111100,
            B01111100,
            B00111000,
            B00010000,
            B00000000
    },
    {
            B01000100,
            B11101110,
            B11010110,
            B11000110,
            B01101100,
            B00111000,
            B00010000
    },
    {
            B01000100,
            B11101110,
            B11111110,
            B11111110,
            B01111100,
            B00111000,
            B00010000
    }
};

class AppletClock : public Applet {

public:
    explicit AppletClock(byte idZone, bool heartEnabled = false, bool dongEnabled = false);
    ~AppletClock();

    bool shouldBePaused(bool isAnimationFinished) override;
    bool shouldBeDestroyed(bool isAnimationFinished) override;
    void refresh() override;
    void draw(MD_Parola *matrix, bool isAnimationFinished) override;
    void printSerial() override;

private:
    Timer heartTimer;
    Timer secondTimer;
    byte currentHeart = 0;
    bool hasDong = false;
    bool heartEnabled = false;
    bool dongEnabled = false;
    char timeStr[10];
};

#endif
