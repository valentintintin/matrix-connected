#include "AppletMessage.h"

AppletMessage::AppletMessage(byte idZone, String message) : Applet(idZone, PSTR("Message")) {
    utf8ToCp437(message);
    message.toCharArray(this->message, MAX_LENGTH_MESSAGE);
}

AppletMessage::~AppletMessage() = default;

bool AppletMessage::shouldBePaused(bool isAnimationFinished) {
    return isAnimationFinished;
}

bool AppletMessage::shouldBeDestroyed(bool isAnimationFinished) {
    return isAnimationFinished;
}

void AppletMessage::draw(MD_Parola *matrix, bool isAnimationFinished) {
    if (isAnimationFinished) {
        matrix->displayReset(getIdZone());
        matrix->displayZoneText(getIdZone(), message, PA_LEFT, matrix->getSpeed(), matrix->getPause(), PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    }
}

void AppletMessage::printSerial() {
    Applet::printSerial(); DPRINT(F("\tMessage: ")); DPRINTLN(message);
}
