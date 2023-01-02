#include "Orchestror.h"

Orchestror::Orchestror(System* system, byte idZone) : idZone(idZone), system(system) {
}

void Orchestror::update() {
    DPRINT(F("[ORCHESTROR ")); DPRINT(idZone); DPRINT(F("]\r\n\t[UPDATE]")); DPRINT(F("NbApplets: ")); DPRINTLN(nbApplets);

    MD_Parola* matrix = system->getMatrix();
    bool animationFinished = matrix->getZoneStatus(idZone);

    Applet *newApplet = nullptr;
    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        Applet *applet = applets[i];

        if (applet == nullptr) {
            continue;
        }

        DPRINT(F("\tBlock ")); DPRINT(i); DPRINT(F("\r\n\t\t"));
        applet->refresh();
        applet->printSerial();

        DPRINT(F("\t\tShould be destroyed: ")); DPRINTLN(applet->shouldBeDestroyed());
        if (applet->shouldBeDestroyed()) {
            destroyApplet(applet);

            // Reset loop
            newApplet = nullptr;
            i = -1;
            continue;
        }

        DPRINT(F("\t\tShould be resumed: ")); DPRINTLN(applet->shouldBeResumed());
        if (applet->shouldBeResumed() // Applet wants to be displayed
            && ( // And
                newApplet == nullptr  // We do not have applet currently on hand
                || applet->getPriority() >= newApplet->getPriority() // Or applet as same or greater priority
            )
        ) {
            newApplet = applet; // Applet is candidate to be displayed
            DPRINT(F("\tNew applet: ")); DPRINTLN(newApplet->getName());
        }
    }

    if (newApplet != nullptr) { // We have a candidate to display
        resumeApplet(newApplet);

        DPRINT(F("\t[Draw]")); DPRINTLN(currentApplet->getName());
        currentApplet->draw(animationFinished);
    } else {
        DPRINTLN(F("No applet to display"));
    }
}

bool Orchestror::addApplet(Applet* applet) {
    DPRINTLN(F("[ORCHESTROR]Add applet"));

    if (nbApplets >= NB_MAX_APPLETS) {
        DPRINTLN(F("\tKO (too much)"));

        return false;
    }

    DPRINT(F("\t"));

    nbApplets++;
    applet->onInit();

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
    if (applet == currentApplet) {
        return;
    }

    if (currentApplet != nullptr) {
        pauseApplet(currentApplet);
    }

    DPRINTLN(F("[ORCHESTROR]Resume applet")); DPRINT(F("\t"));
    applet->onResume();

    currentApplet = applet;
}

void Orchestror::pauseApplet(Applet* applet) {
    DPRINTLN(F("[ORCHESTROR]Pause applet")); DPRINT(F("\t"));

    applet->onPause();

    if (applet == currentApplet) {
        currentApplet = nullptr;

        DPRINTLN(F("[ORCHESTROR]Pause applet : display clear"));
        system->getMatrix()->setTextEffect(idZone, PA_PRINT, PA_PRINT);
    }
}

void Orchestror::destroyApplet(Applet* applet) {
    DPRINTLN(F("[ORCHESTROR]Destroy applet")); DPRINT(F("\t"));

    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        Applet *appletI = applets[i]; // Applet in this place

        if (appletI == nullptr) {
            continue;
        }

        if (appletI == applet) {
            if (applet == currentApplet) {
                pauseApplet(applet);
            }

            applet->onDestroy();

            nbApplets--;
            applets[i] = nullptr;

            return;
        }
    }
}

Applet *Orchestror::getAppletByType(const byte type) {
    for (auto applet : applets) {
        if (applet != nullptr && applet->getType() == type) {
            return applet;
        }
    }

    return nullptr;
}

void Orchestror::setDisplayed(bool state) {
    isDisplayed = state;

    if (!state) {
        for (auto applet: applets) {
            if (applet != nullptr && applet->isDisplayed()) {
                pauseApplet(applet);
                return;
            }
        }
    }
}
