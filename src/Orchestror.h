#ifndef MATRIX_CONNECTED_ORCHESTROR_H
#define MATRIX_CONNECTED_ORCHESTROR_H

#define NB_MAX_APPLETS 16

#include "Applet.h"

class Orchestror {
public:
    Orchestror();

    void update();

private:
    Applet* applets[NB_MAX_APPLETS];
};


#endif //MATRIX_CONNECTED_ORCHESTROR_H
