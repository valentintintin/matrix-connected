#include "Applet.h"
#include "../FontData.h"

long Applet::APPLET_ID = 1;

Applet::Applet(Orchestror *orchestror, const char* name, const byte type, const byte priority) : orchestror(orchestror), type(type), priority(priority), id(APPLET_ID++) {
    strcpy_P(this->name, name);
    getMatrix()->getDisplayExtent(getIdZone(), startColumn, endColumn);
}

void Applet::onInit() {
}

void Applet::onPause() {
    displayed = false;
}

void Applet::onResume() {
    displayed = true;
    getMatrix()->setFont(getIdZone(), font);
}

void Applet::refresh() {
}

void Applet::printSerial() {
    DPRINT(F("[APPLET]")); DPRINT(getName()); DPRINT(F(", Zone: ")); DPRINT(getIdZone()); DPRINT(F(", Displayed: ")); DPRINTLN(isDisplayed());
}

byte Applet::getIdZone() const {
    return orchestror->getIdZone();
}

MD_Parola* Applet::getMatrix() const {
    return orchestror->getSystem()->getMatrix();
}
