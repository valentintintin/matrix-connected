#ifndef MATRIX_CONNECTED_ORCHESTROR_H
#define MATRIX_CONNECTED_ORCHESTROR_H

#define NB_MAX_APPLETS 16

#include <Arduino.h>

#include "Applet.h"
#include "Utils.h"

class Orchestror {
public:
    Orchestror(MD_Parola* matrix);

    void setState(bool newState);
    void update();

    void addApplet(Applet* applet);
    void pauseApplet(Applet* applet);
    void resumeApplet(Applet* applet);
    void destroyApplet(byte iApplet);

private:
    void displayNextApplet(byte idZone, Applet* toExclude = nullptr);

    bool state = true;
    byte nbApplets = 0;
    Applet* applets[NB_MAX_APPLETS];
    MD_Parola* matrix;
};


#endif //MATRIX_CONNECTED_ORCHESTROR_H
