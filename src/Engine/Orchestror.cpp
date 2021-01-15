#include "Orchestror.h"

Orchestror::Orchestror(MD_Parola* matrix) : matrix(matrix) {
    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        applets[i] = nullptr;
    }
}

void Orchestror::update() {
    DPRINT(F("[ORCHESTROR]\r\n\t[UPDATE]State: ")); DPRINT(state); DPRINT(F(", NbApplets: ")); DPRINTLN(nbApplets);

    if (state) {
        matrix->synchZoneStart();
        matrix->displayAnimate();
    } else {
        // fake delay for CPU stress
        delay(matrix->getSpeed());
    }

    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        Applet* applet = applets[i];

        if (applet != nullptr) {
            bool zoneFinished = matrix->getZoneStatus(applet->getIdZone());

            DPRINT(F("\tBlock ")); DPRINT(i); DPRINT(F(", zoneFinished: ")); DPRINT(zoneFinished); DPRINT(F("\r\n\t\t")); applet->printSerial();

            applet->refresh();

            if (applet->isDisplayed()) {
                if (applet->shouldBeDestroyed(zoneFinished)) {
                    destroyApplet(i);

                    continue;
                } else if (applet->shouldBePaused(zoneFinished)) {
                    pauseApplet(applet);

                    continue;
                }

                DPRINTLN(F("\t[Draw]"));
                applet->draw(matrix, zoneFinished);
            }
        }
    }
}

void Orchestror::addApplet(Applet* applet) {
    DPRINTLN(F("[ORCHESTROR]Add applet"));

    if (nbApplets >= NB_MAX_APPLETS) {
        DPRINTLN(F("\tKO (too much)"));

        return;
    }

    DPRINT(F("\t"));

    nbApplets++;
    applet->onInit();

    // Add new applet and find if there is already one which is displayed
    Applet* currentAppletDisplayedInZone = nullptr;
    bool appledAdded = false;

    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        Applet *appletFor = applets[i]; // Applet in this place

        if (!appledAdded && appletFor == nullptr) { // Free block, new applet add in this place
            DPRINT(F("\tFound block ")); DPRINTLN(i);

            applets[i] = applet;
            appledAdded = true;

            continue; // Nothing more to do
        }

        if (appletFor != nullptr && currentAppletDisplayedInZone == nullptr) {
            if (
                appletFor->getIdZone() == applet->getIdZone() // Same zone
                && appletFor->isDisplayed() // Currently displayed
            ) {
                DPRINT(F("\tFound already displayed applet in zone in block ")); DPRINTLN(i);

                currentAppletDisplayedInZone = appletFor;

                if (appledAdded) {
                    break; // We have everything so we break the loop
                }
            }
        }
    }

    if (currentAppletDisplayedInZone != nullptr) {
        if (currentAppletDisplayedInZone->getPriority() < applet->getPriority()) {
            resumeApplet(applet);
        } else {
            pauseApplet(applet, false);
        }
    } else {
        resumeApplet(applet);
    }
}

void Orchestror::resumeApplet(Applet* applet) {
    DPRINTLN(F("[ORCHESTROR]Resume applet")); DPRINT(F("\t"));

    applet->OnResume();
    applet->draw(matrix, true);
}

void Orchestror::pauseApplet(Applet* applet, bool displayNext) {
    DPRINTLN(F("[ORCHESTROR]Pause applet")); DPRINT(F("\t"));

    applet->onPause();

    if (displayNext) {
        displayNextApplet(applet->getIdZone(), applet);
    }
}

void Orchestror::destroyApplet(byte iApplet) {
    DPRINTLN(F("[ORCHESTROR]Destroy applet")); DPRINT(F("\t"));

    Applet* applet = applets[iApplet];

    displayNextApplet(applet->getIdZone(), applet);

    applet->onDestroy();
    nbApplets--;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-abstract-non-virtual-dtor"
    delete applet;
#pragma clang diagnostic pop

    applets[iApplet] = nullptr;
}

void Orchestror::setState(bool newState) {
    DPRINTLN(F("[ORCHESTROR]Change state to ")); DPRINTLN(state);

    state = newState;

    matrix->displayShutdown(!state);
}

void Orchestror::displayNextApplet(byte idZone, Applet* toExclude) {
    DPRINT(F("[ORCHESTROR]Display next Applet zone ")); DPRINTLN(idZone);

    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        if (applets[i] != nullptr) {
            Applet *appletFor = applets[i]; // Applet in this place

            if (appletFor->getIdZone() == idZone && (toExclude == nullptr || toExclude->getId() != appletFor->getId())) { // Same zone and not current
                DPRINTLN(F("\t[ORCHESTROR]Found applet to display"));

                resumeApplet(appletFor);
                break; // We have everything so we break the loop
            }
        }
    }
}
