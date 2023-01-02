#ifndef APPLET_CAR_H
#define APPLET_CAR_H

#include "AppletSymbolsAnimated.h"
#include "FontData.h"

class AppletCar : public AppletSymbolsAnimated {

public:
    explicit AppletCar(Orchestror *orchestror): AppletSymbolsAnimated(orchestror, PSTR("CAR"), {
            cars,
            2,
            {
                    { 500, 0 },
                    { 250, 1 },
            }
    }) {
    }
};

#endif
