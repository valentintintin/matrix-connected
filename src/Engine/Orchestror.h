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

    void addApplet(Applet* applet);
    void pauseApplet(Applet* applet, bool displayNext = true);
    void resumeApplet(Applet* applet);
    void destroyApplet(byte iApplet);

    inline const byte getIdZone() const {
        return idZone;
    }

    inline System* getSystem() {
        return system;
    }

private:
    const byte idZone;
    byte nbApplets = 0;
    Applet* currentApplet = nullptr;
    Applet* applets[NB_MAX_APPLETS];
    System* system;
};


#endif //MATRIX_CONNECTED_ORCHESTROR_H
