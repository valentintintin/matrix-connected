#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <PPMax72xxPanel.h>
#include <Queue.h>
#include <Ticker.h>

#define MAX_SLIDES_IN_QUEUE 10

class Slide;

class Screen {

public:
    explicit Screen(byte csPin, byte hDisplays, byte soundPin = 255, byte ledPin = 255);

    void addSlide(Slide *slide);

    void setMainSlide(Slide *slide);

    void setFallBackSlide(Slide *slide);

    const Slide *getMainSlide();

    bool refresh();

    void setState(bool on);

    PPMax72xxPanel matrix;

    void setSongToPlay(const char *song);

    void setLed(bool status);

    void setBlink();

private:
    void printSlides();

    void blinkProcess();

    byte soundPin = 255; // disabled
    byte ledPin = 255; // disabled

    Slide *mainSlide = nullptr;
    Slide *fallBackSlide = nullptr;
    Queue<Slide *> slides = Queue<Slide *>(MAX_SLIDES_IN_QUEUE);

    bool enabled = false;

    Ticker blinkTicker;
    byte blinkCounter;
};

#endif