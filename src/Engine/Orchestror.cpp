#include "Orchestror.h"

Orchestror::Orchestror(System* system, byte idZone) : idZone(idZone), system(system) {
}

void Orchestror::update() {
    MD_Parola* matrix = system->getMatrix();
    bool animationFinished = matrix->getZoneStatus(idZone);

    Applet *newApplet = nullptr;
    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        Applet *applet = applets[i];

        if (applet == nullptr) {
            continue;
        }

        applet->refresh();
        applet->printSerial();

        if (applet->shouldBeResumed(animationFinished) // Applet wants to be displayed
            && ( // And
                newApplet == nullptr  // We do not have applet currently on hand
                || applet->getPriority() >= newApplet->getPriority() // Or applet as same or greater priority
            )
        ) {
            newApplet = applet; // Applet is candidate to be displayed
        }
    }

    if (newApplet != nullptr) { // We have a candidate to display
        resumeApplet(newApplet);

        currentApplet->draw(animationFinished);
    }
}

bool Orchestror::addApplet(Applet* applet) {
    if (nbApplets >= NB_MAX_APPLETS) {
        return false;
    }

    nbApplets++;
    applet->onInit();

    // Add new applet and find if there is already one which is displayed
    for (byte i = 0; i < NB_MAX_APPLETS; i++) {
        Applet *appletFor = applets[i]; // Applet in this place

        if (appletFor == nullptr) { // Free block, new applet add in this place
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

    applet->onResume();

    currentApplet = applet;
}

void Orchestror::pauseApplet(Applet* applet) {
    applet->onPause();

    if (applet == currentApplet) {
        currentApplet = nullptr;

        system->getMatrix()->displayClear(getIdZone());
        system->getMatrix()->setTextEffect(idZone, PA_PRINT, PA_PRINT);
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
