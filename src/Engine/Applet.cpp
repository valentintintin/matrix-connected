#include "Applet.h"

long Applet::APPLET_ID = 1;

Applet::Applet(Orchestror *orchestror, const char* name, const byte type, const byte priority) : orchestror(orchestror), type(type), priority(priority), id(APPLET_ID++) {
    strcpy_P(this->name, name);
    DPRINT(F("[APPLET NEW] ")); printSerial();
    getMatrix()->getDisplayExtent(getIdZone(), startColumn, endColumn);
}

void Applet::onInit() {
    printSerial(); DPRINTLN(F("\tInitiated"));
}

void Applet::onPause() {
    printSerial(); DPRINTLN(F("\tPaused"));
    displayed = false;
}

void Applet::onResume() {
    printSerial(); DPRINTLN(F("\tResumed"));
    displayed = true;
}

void Applet::onDestroy() {
    printSerial(); DPRINTLN(F("\tDestroyed"));
}

void Applet::refresh() {
}

void Applet::printSerial() {
    DPRINT(F("[APPLET]")); DPRINT(getName()); DPRINT(F("(")); DPRINT(orchestror->getIdZone()); DPRINT(F(")")); DPRINT(F(", Zone: ")); DPRINT(getIdZone()); DPRINT(F(", Displayed: ")); DPRINTLN(isDisplayed());
}

byte Applet::getIdZone() const {
    return orchestror->getIdZone();
}

MD_Parola* Applet::getMatrix() const {
    return orchestror->getSystem()->getMatrix();
}
