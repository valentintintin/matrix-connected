#include "Applet.h"

long Applet::APPLET_ID = 1;

Applet::Applet(const Orchestror *orchestror, const char* name, byte priority) : orchestror(orchestror), priority(priority), id(APPLET_ID++) {
    strcpy_P(this->name, name);
    DPRINT(F("[APPLET NEW] ")); printSerial();
}

Applet::~Applet() {
}


void Applet::onInit(MD_Parola *matrix) {
    printSerial(); DPRINTLN(F("\tInitiated"));
    matrix->getDisplayExtent(getIdZone(), startColumn, endColumn);
}

void Applet::onPause() {
    printSerial(); DPRINTLN(F("\tPaused"));

    displayed = false;
}

void Applet::onResume(MD_Parola *matrix) {
    printSerial(); DPRINTLN(F("\tResumed"));

    displayed = true;
    refresh();

    matrix->displayClear(getIdZone());
}

void Applet::onDestroy() {
    printSerial(); DPRINTLN(F("\tDestroyed"));
}

void Applet::refresh() {
}

void Applet::printSerial() {
    DPRINT(F("[APPLET]")); DPRINT(getName()); DPRINT(F("(")); DPRINT(orchestror->getIdZone()); DPRINT(F(")")); DPRINT(F(", Zone: ")); DPRINT(getIdZone()); DPRINT(F(", Displayed: ")); DPRINTLN(isDisplayed());
}

const byte Applet::getIdZone() const {
    return orchestror->getIdZone();
}
