#include "System.h"
#include "FontData.h"

#include "Applets/AppletHeart.h"
#include "Applets/AppletScreenSaver.h"
#include "Applets/AppletMessage.h"
#include "Applets/AppletClock.h"

System::System(MD_Parola *matrix) : matrix(matrix) {
    DPRINTLN(F("[MATRIX]Start"));
    matrix->begin(3);
    matrix->setZone(ZONE_RIGHT, 0, 9);
    matrix->setZone(ZONE_LEFT, 10, 14);
    matrix->setZone(ZONE_HEART, 15, 15);
    matrix->setIntensity(3);
    matrix->setPause(0);
    matrix->setSpeed(20);
    matrix->setFont(font);

    orchestrors[ZONE_HEART] = new Orchestror(this, (byte) ZONE_HEART);
    orchestrors[ZONE_LEFT] = new Orchestror(this, ZONE_LEFT);
    orchestrors[ZONE_RIGHT] = new Orchestror(this, ZONE_RIGHT);

    DPRINT(F("[ORCHESTROR]")); DPRINT(NB_MAX_APPLETS); DPRINTLN(F(" applets max"));
    orchestrors[ZONE_HEART]->addApplet(new AppletHeart(orchestrors[ZONE_HEART]));
    orchestrors[ZONE_LEFT]->addApplet(new AppletClock(orchestrors[ZONE_LEFT]));

    appletMessage = new AppletMessage(orchestrors[ZONE_RIGHT]);
    orchestrors[ZONE_RIGHT]->addApplet(appletMessage);
    orchestrors[ZONE_RIGHT]->addApplet(new AppletScreenSaver(orchestrors[ZONE_RIGHT]));
}

void System::setMatrixActivated(bool activated) {
    DPRINTLN(F("[ORCHESTROR]Change matrixActivated to ")); DPRINTLN(matrixActivated);

    matrixActivated = activated;

    matrix->displayShutdown(!matrixActivated);
}

void System::update() {
    DPRINT(F("[SYSTEM]MatrixActivated: ")); DPRINT(isMatrixActivated()); DPRINTLN(F("]\r\n\t[UPDATE]"));

    if (isMatrixActivated()) {
        matrix->displayAnimate();

        for (auto orchestror : orchestrors) {
            orchestror->update();
        }
    } else {
        // fake delay for CPU stress
        delay(matrix->getSpeed());
    }

//    if (dongEnabled && hour() != 0 && minute() == 0 && second() == 0) {
//        if (!hasDong) {
//            screen->setSongToPlay(dong);
//            screen->setBlink();
//            hasDong = true;
//        }
//    } else {
//        hasDong = false;
//    }
}