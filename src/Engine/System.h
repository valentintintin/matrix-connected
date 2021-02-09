#ifndef MATRIX_CONNECTED_SYSTEM_H
#define MATRIX_CONNECTED_SYSTEM_H

#include <MD_Parola.h>

#include "Orchestror.h"
#include "Utils.h"

class AppletMessage;

#define NB_MAX_ORCHESTROR 3

#define ZONE_HEART 0
#define ZONE_LEFT 1
#define ZONE_RIGHT 2

const char PROGMEM dong[] = "dong:d=10,o=6,b=180,c,e,g";

class System {
public:
    explicit System(MD_Parola *matrix);

    void setMatrixActivated(bool activated);
    void update();

    inline const bool isMatrixActivated() const {
        return matrixActivated;
    }

    inline MD_Parola* getMatrix() {
        return matrix;
    }

    inline Orchestror* getOrchestorForZone(byte idZone) {
        return orchestrors[idZone];
    }

    inline AppletMessage* getAppletMessage() {
        return appletMessage;
    }

private:
    bool matrixActivated = true;
    MD_Parola* matrix;

    Orchestror* orchestrors[NB_MAX_ORCHESTROR];
    AppletMessage* appletMessage;
};


#endif //MATRIX_CONNECTED_SYSTEM_H
