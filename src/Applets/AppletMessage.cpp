#include "AppletMessage.h"
#include "../Engine/Utils.h"

AppletMessage::AppletMessage(Orchestror *orchestror) : Applet(orchestror, PSTR("Message"), MESSAGE, 15) {
    message[0] = '\0';
}

bool AppletMessage::shouldBeResumed(bool animationFinished) {
    return hasMessage;
}

bool AppletMessage::shouldBeDestroyed(bool animationFinished) {
    return false;
}

void AppletMessage::draw(bool animationFinished) {
    if (animationFinished) {
        if (!messages.isEmpty()) {
            popMessage();
            getMatrix()->displayZoneText(getIdZone(), message, PA_LEFT, 25, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        } else {
            hasMessage = false;
            message[0] = '\0';
        }
    }
}

void AppletMessage::printSerial() {
    Applet::printSerial(); DPRINT(F("\tMessage: ")); DPRINT(message); DPRINT(F(", Nb message: ")); DPRINT(messages.itemCount()); DPRINT(F(", Has messages: ")); DPRINTLN(hasMessage);
}

void AppletMessage::addMessage(const char* messageToAdd) {
    Applet::printSerial(); DPRINT(F("\tAddMessage: ")); DPRINT(messageToAdd); DPRINT(F(", Nb message: ")); DPRINT(messages.itemCount()); DPRINT(F(", Has messages: ")); DPRINTLN(hasMessage);

    if (!messages.isEmpty()) {
        char* messageToShow = (char*)malloc ((strlen(messageToAdd) + 1) * sizeof (char));
        strcpy(messageToShow, messageToAdd);

        utf8Ascii(messageToShow);

        messages.enqueue(messageToShow);
        hasMessage = true;
    } else {
        DPRINTLN(F("Too much messages, leave it !"));
    }
}

void AppletMessage::popMessage() {
    char* newMessage = messages.dequeue();
    DPRINT(F("New message: ")); DPRINTLN(newMessage); DPRINT(F(", Nb message: ")); DPRINT(messages.itemCount()); DPRINT(F(", Has messages: ")); DPRINTLN(hasMessage);

    strcpy(this->message, newMessage);

    delete newMessage;
}