#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
//#include <Adafruit_GFX.h>
//#include <PPMax72xxPanel.h>
//#include <Queue.h>
//#include <Ticker.h>

#define MAX_APPLETS_IN_QUEUE 10

class Applet;

class Screen {

public:
    explicit Screen(byte csPin, byte hDisplays, byte soundPin = 255, byte ledPin = 255);

    void addApplet(Applet *slide);

    void setMainApplet(Applet *slide);

    void setFallBackApplet(Applet *slide);

    const Applet *getMainApplet();

    bool refresh();

    void setState(bool on);
    
    void setIntensity(byte intensity);

//    PPMax72xxPanel matrix;

    void setSongToPlay(const char *song);

    void setLed(bool status);

    void setBlink();

private:
    void printApplets();

    void blinkProcess();

    byte soundPin = 255; // disabled
    byte ledPin = 255; // disabled
    byte intensity = 0;

    Applet *mainApplet = nullptr;
    Applet *fallBackApplet = nullptr;
//    Queue<Applet *> slides = Queue<Applet *>(MAX_APPLETS_IN_QUEUE);

    bool enabled = false;

//    Ticker blinkTicker;
    byte blinkCounter;
};

#endif
