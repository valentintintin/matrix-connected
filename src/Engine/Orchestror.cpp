#include "Orchestror.h"

Orchestror::Orchestror(System* system, byte idZone) : idZone(idZone), system(system) {
    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        applets[i] = nullptr;
    }
}

void Orchestror::update() {
    DPRINT(F("[ORCHESTROR ")); DPRINT(idZone); DPRINT(F("]\r\n\t[UPDATE]")); DPRINT(F("NbApplets: ")); DPRINTLN(nbApplets);

    MD_Parola* matrix = system->getMatrix();
    bool zoneFinished = matrix->getZoneStatus(idZone);

    Applet* appletMaxPriority = nullptr;
    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        Applet *applet = applets[i];

        if (applet != nullptr) {
            DPRINT(F("\tBlock ")); DPRINT(i); DPRINT(F(", zoneFinished: ")); DPRINT(zoneFinished); DPRINT(F("\r\n\t\t")); applet->printSerial();

            applet->refresh();

            if (applet->shouldBeDestroyed(zoneFinished)) {
                destroyApplet(i);

                continue;
            }

            if (!applet->shouldBePaused(zoneFinished)
                && (currentApplet == nullptr || appletMaxPriority == nullptr || applet->getPriority() > appletMaxPriority->getPriority())
            ) {
                appletMaxPriority = applet;
            }
        }
    }

    if (currentApplet == nullptr && appletMaxPriority != nullptr) {
        resumeApplet(appletMaxPriority);
    }

    if (currentApplet != nullptr) {
        if (appletMaxPriority != nullptr && currentApplet->getId() != appletMaxPriority->getId()) {
            resumeApplet(appletMaxPriority);
        }

        DPRINTLN(F("\t[Draw]"));
        currentApplet->draw(matrix, zoneFinished);
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
}

void Orchestror::resumeApplet(Applet* applet) {
    DPRINTLN(F("[ORCHESTROR]Resume applet")); DPRINT(F("\t"));

    if (currentApplet != nullptr) {
        pauseApplet(currentApplet);
    }

    applet->onResume(system->getMatrix());

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
