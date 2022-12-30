#include "Orchestror.h"

Orchestror::Orchestror(System* system, byte idZone) : idZone(idZone), system(system) {
    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        applets[i] = nullptr;
    }
}

void Orchestror::update() {
    DPRINT(F("[ORCHESTROR ")); DPRINT(idZone); DPRINT(F("]\r\n\t[UPDATE]")); DPRINT(F("NbApplets: ")); DPRINTLN(nbApplets);

    MD_Parola* matrix = system->getMatrix();

    if (matrix->getZoneStatus(idZone)) { // Zone animation finished
        Applet *newApplet = nullptr;
        for (byte i = 0; i < NB_MAX_APPLETS; i++) {
            Applet *applet = applets[i];

            if (applet != nullptr) {
                DPRINT(F("\tBlock ")); DPRINT(i); DPRINT(F("\r\n\t\t"));
                applet->printSerial();

                applet->refresh();

                DPRINT(F("\t\tShould be destroyed: ")); DPRINTLN(applet->shouldBeDestroyed());

                if (applet->shouldBeDestroyed()) {
                    destroyApplet(i);
                    continue;
                }

                DPRINT(F("\t\tShould be paused: ")); DPRINTLN(applet->shouldBeResumed());

                if (applet->shouldBeResumed()
                    && (newApplet == nullptr || applet->getPriority() >= newApplet->getPriority())
                        ) {
                    newApplet = applet;
                    DPRINT(F("\tNew applet: ")); DPRINTLN(newApplet->getName());
                }
            }
        }

        if (newApplet != nullptr) {
            resumeApplet(newApplet);

            DPRINT(F("\t[Draw]")); DPRINTLN(currentApplet->getName());
            currentApplet->draw(matrix);
        } else {
            DPRINTLN(F("No applet"));
        }
    }

    matrix->synchZoneStart();
}

bool Orchestror::addApplet(Applet* applet) {
    DPRINTLN(F("[ORCHESTROR]Add applet"));

    if (nbApplets >= NB_MAX_APPLETS) {
        DPRINTLN(F("\tKO (too much)"));

        return false;
    }

    DPRINT(F("\t"));

    nbApplets++;
    applet->onInit(system->getMatrix());

    // Add new applet and find if there is already one which is displayed
    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        Applet *appletFor = applets[i]; // Applet in this place

        if (appletFor == nullptr) { // Free block, new applet add in this place
            DPRINT(F("\tFound block ")); DPRINTLN(i);

            applets[i] = applet;

            break; // Nothing more to do
        }
    }

    return true;
}

void Orchestror::resumeApplet(Applet* applet) {
    DPRINTLN(F("[ORCHESTROR]Resume applet")); DPRINT(F("\t"));

    if (applet != currentApplet) {
        if (currentApplet != nullptr) {
            pauseApplet(currentApplet);
        }

        applet->onResume(system->getMatrix());
    }

    currentApplet = applet;
}

void Orchestror::pauseApplet(Applet* applet, bool displayNext) {
    DPRINTLN(F("[ORCHESTROR]Pause applet")); DPRINT(F("\t"));

    applet->onPause();

    currentApplet = nullptr;
}

void Orchestror::destroyApplet(byte iApplet) {
    DPRINTLN(F("[ORCHESTROR]Destroy applet")); DPRINT(F("\t"));

    Applet* applet = applets[iApplet];

    if (applet == currentApplet) {
        currentApplet = nullptr;
    }

    applet->onDestroy();
    nbApplets--;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-abstract-non-virtual-dtor"
    delete applet;
#pragma clang diagnostic pop

    applets[iApplet] = nullptr;
}

Applet *Orchestror::getAppletByType(const byte type) {
    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        Applet *applet = applets[i]; // Applet in this place

        if (applet != nullptr && applet->getType() == type) {
            return applet;
        }
    }

    return nullptr;
}
