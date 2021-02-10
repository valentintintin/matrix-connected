#ifndef APPLET_HEART_H
#define APPLET_HEART_H

#include "../Engine/Applet.h"

#define HEART_PULSE_MS 325

MD_MAX72XX::fontType_t hearts[] PROGMEM =
{
    0, 	// 0
    6, 0, 12, 18, 36, 18, 12, 	        // 0  Small
    6, 0, 12, 30, 60, 30, 12, 	        // 1  SmallFilled
    7, 14, 31, 50, 100, 50, 31, 14, 	// 2  Large
    7, 14, 31, 62, 124, 62, 31, 14, 	// 3  LargeFilled
};

class AppletHeart : public Applet {

public:
    AppletHeart(Orchestror *orchestror);

    void onResume(MD_Parola* matrix) override;
    bool shouldBePaused(bool isAnimationFinished) override;
    bool shouldBeDestroyed(bool isAnimationFinished) override;
    void draw(MD_Parola *matrix, bool isAnimationFinished) override;
    void printSerial() override;

private:
    void setIntensity(MD_Parola *matrix);

    char heartStr[1];
    byte currentHeart = 0;
};

#endif
