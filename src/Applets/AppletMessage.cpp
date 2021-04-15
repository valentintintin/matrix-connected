#include "AppletMessage.h"

AppletMessage::AppletMessage(Orchestror *orchestror) : Applet(orchestror, PSTR("Message"), MESSAGE, 10) {
    strcpy_P(message, PSTR(""));
}

bool AppletMessage::shouldBePaused(bool isAnimationFinished) {
    return isAnimationFinished && messages.count() == 0;
}

bool AppletMessage::shouldBeDestroyed(bool isAnimationFinished) {
    return false;
}

void AppletMessage::draw(MD_Parola *matrix, bool isAnimationFinished) {
    if (isAnimationFinished && messages.count() > 0) {
        char* newMessage = messages.pop();
        DPRINT(F("New message: ")); DPRINTLN(newMessage); DPRINT(F(", Nb message: ")); DPRINTLN(messages.count());

        strcpy(this->message, newMessage);

        delete newMessage;

        matrix->displayReset(getIdZone());
    }
}

void AppletMessage::printSerial() {
    Applet::printSerial(); DPRINT(F("\tMessage: ")); DPRINT(message); DPRINT(F(", Nb message: ")); DPRINTLN(messages.count());
}

void AppletMessage::addMessage(String messageToAdd) {
    Applet::printSerial(); DPRINT(F("\tAddMessage: ")); DPRINT(messageToAdd); DPRINT(F(", Nb message: ")); DPRINTLN(messages.count());

    if (messages.count() < MAX_MESSAGES) {
        char* messageToShow = (char*)malloc ((messageToAdd.length() + 1) * sizeof (char));;
        utf8ascii(messageToAdd).toCharArray(messageToShow, messageToAdd.length() + 1);
        messages.push(messageToShow);
    } else {
        DPRINTLN(F("Too much messages, leave it !"));
    }
}

void AppletMessage::addMessage(char* messageToAdd) {
    Applet::printSerial(); DPRINT(F("\tAddMessage: ")); DPRINT(messageToAdd); DPRINT(F(", Nb message: ")); DPRINTLN(messages.count());

    if (messages.count() < MAX_MESSAGES) {
        char* messageToShow = (char*)malloc ((strlen(messageToAdd) + 1) * sizeof (char));
        strcpy(messageToShow, messageToAdd);
        messages.push(messageToShow);
    } else {
        DPRINTLN(F("Too much messages, leave it !"));
    }
}

void AppletMessage::onResume(MD_Parola *matrix) {
    Applet::onResume(matrix);

    matrix->displayZoneText(getIdZone(), message, PA_LEFT, 25, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}
