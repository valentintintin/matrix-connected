#ifndef APPLET_HEART_H
#define APPLET_HEART_H

#include "AppletSymbolsAnimated.h"
#include "FontData.h"

#define HEART_PULSE_MS 325

class AppletHeart : public AppletSymbolsAnimated {

public:
    explicit AppletHeart(Orchestror *orchestror): AppletSymbolsAnimated(orchestror, PSTR("HEAR"), {
            hearts,
            4,
            {
                    { HEART_PULSE_MS, 1 },
                    { HEART_PULSE_MS, 3 },
                    { HEART_PULSE_MS, 1 },
                    { HEART_PULSE_MS, 3 },
            }
    }) {
    }
};

#endif
