#include "Applet.h"

long Applet::APPLET_ID = 1;

Applet::Applet(Orchestror* orchestror, byte idZone, const char* name, byte priority) : orchestror(orchestror), idZone(idZone), priority(priority), id(APPLET_ID++) {
    strcpy_P(this->name, name);
    DPRINT(F("[APPLET NEW] ")); printSerial();
}

Applet::~Applet() {
}


void Applet::onInit() {
    printSerial(); DPRINTLN(F("\tInitiated"));
}

void Applet::onPause() {
    printSerial(); DPRINTLN(F("\tPaused"));

    displayed = false;
}

void Applet::OnResume() {
    printSerial(); DPRINTLN(F("\tResumed"));

    displayed = true;
    refresh();
}

void Applet::onDestroy() {
    printSerial(); DPRINTLN(F("\tDestroyed"));
}

void Applet::refresh() {
}

void Applet::printSerial() {
    DPRINT(F("[APPLET]")); DPRINT(getName()); DPRINT(F("(")); DPRINT(id); DPRINT(F(")")); DPRINT(F(", Zone: ")); DPRINT(getIdZone()); DPRINT(F(", Displayed: ")); DPRINTLN(isDisplayed());
}