#ifndef APPLET_HEART_H
#define APPLET_HEART_H

#include "../Engine/Applet.h"
#include "../Engine/Timer.h"

#define HEART_PULSE_MS 250

MD_MAX72XX::fontType_t hearts[] PROGMEM =
{
    0, 	// 0
    6, 0, 12, 18, 36, 18, 12, 	// 0  Small
    6, 0, 12, 30, 60, 30, 12, 	// 1  SmallFilled
    7, 14, 31, 50, 100, 50, 31, 14, 	// 2  Large
    7, 14, 31, 62, 124, 62, 31, 14, 	// 3  LargeFilled
};

class AppletHeart : public Applet {

public:
    explicit AppletHeart(Orchestror* orchestror, byte idZone);
    ~AppletHeart();

    bool shouldBePaused(bool isAnimationFinished) override;
    bool shouldBeDestroyed(bool isAnimationFinished) override;
    void refresh() override;
    void draw(MD_Parola *matrix, bool isAnimationFinished) override;
    void printSerial() override;

private:
    Timer heartTimer;
    char heartStr[1];
    byte currentHeart = 0;
};

#endif
