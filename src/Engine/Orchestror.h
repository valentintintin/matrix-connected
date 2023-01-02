#ifndef MATRIX_CONNECTED_ORCHESTROR_H
#define MATRIX_CONNECTED_ORCHESTROR_H

#define NB_MAX_APPLETS 10

#include <Arduino.h>

class Applet;
class System;

#include "Applet.h"
#include "System.h"
#include "Utils.h"

class Orchestror {
public:
    Orchestror(System* system, byte idZone);

    void update();

    bool addApplet(Applet* applet);
    void pauseApplet(Applet* applet);
    void resumeApplet(Applet* applet);
    void destroyApplet(Applet* applet);
    void setDisplayed(bool state);

    Applet* getAppletByType(byte type);

    inline byte getIdZone() const {
        return idZone;
    }

    inline System* getSystem() {
        return system;
    }

    inline bool shouldBeDisplayed() const {
        return isDisplayed;
    }

private:
    const byte idZone;
    byte nbApplets = 0;
    Applet* currentApplet = nullptr;
    Applet* applets[NB_MAX_APPLETS]{nullptr};
    System* system;
    bool isDisplayed = true;
};


#endif //MATRIX_CONNECTED_ORCHESTROR_H
