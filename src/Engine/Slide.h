#ifndef SLIDE_H
#define SLIDE_H

#include <Arduino.h>
#include <PPmax72xxAnimate.h>

#include "Engine/Screen.h"
#include "Engine/Timer.h"

#define TIME_DISPLAYED 5000
#define ANIMATION_SPEED 15

class Slide {

public:
    explicit Slide(Screen *screen);

    virtual ~Slide() {}

    void create();

    void setZone(uint16_t startX = 0, uint16_t widthX = 0, textEffect_t textEffect = _SCROLL_LEFT);

    virtual String getText() = 0;

    bool show();

    virtual bool isFinished() = 0;

    virtual bool shouldRecreate() = 0;

    void print();

protected:
    Screen *screen = nullptr;
    PPmax72xxAnimate zone;

    uint16_t startX = 0;
    uint16_t widthX = 0;
    textEffect_t textEffect = _SCROLL_LEFT;

    Timer timer;

    bool baseIsFinished();
};

#endif