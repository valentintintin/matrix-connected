#include "Applet.h"

Applet::Applet(byte idZone, const char* name, byte priority) : idZone(idZone), priority(priority) {
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
    DPRINT(F("[APPLET]")); DPRINT(getName()); DPRINT(F("(")); DPRINT(getIdZone()); DPRINT(F(")")); DPRINT(F(", Displayed: ")); DPRINTLN(isDisplayed());
}