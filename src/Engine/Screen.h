#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <PPMax72xxPanel.h>
#include <Queue.h>

#define MAX_SLIDES_IN_QUEUE 10

class Slide;

class Screen {

public:
    explicit Screen(byte csPin, byte hDisplays);

    void addSlide(Slide *slide);

    void setMainSlide(Slide *slide);

    void setFallBackSlide(Slide *slide);

    const Slide *getMainSlide();

    bool refresh();

    void setState(bool on);

    PPMax72xxPanel matrix;

private:
    void printSlides();

    Slide *mainSlide = nullptr;
    Slide *fallBackSlide = nullptr;
    Queue<Slide *> slides = Queue<Slide *>(MAX_SLIDES_IN_QUEUE);
    bool enabled = true;
};

#endif