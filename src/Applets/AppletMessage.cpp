#include "AppletMessage.h"
#include "../Engine/Utils.h"

AppletMessage::AppletMessage(Orchestror *orchestror) : Applet(orchestror, PSTR("Message"), MESSAGE, 15) {
    message[0] = '\0';
}

bool AppletMessage::shouldBeResumed(bool animationFinished) {
    return hasMessage;
}

void AppletMessage::draw(bool animationFinished) {
    if (animationFinished) {
        if (isLoopMessage && !timer.hasExpired()) {
            hasMessage = true;
        } else if (!messages.isEmpty()) {
            popMessage();
            hasMessage = true;
        } else {
            hasMessage = false;
            message[0] = '\0';
        }

        if (hasMessage) {
            getMatrix()->displayZoneText(getIdZone(), message, PA_LEFT, 25, 0,
                                         getMatrix()->getZoneEffect(getIdZone(), PA_FLIP_LR) ? PA_SCROLL_RIGHT : PA_SCROLL_LEFT,
                                         getMatrix()->getZoneEffect(getIdZone(), PA_FLIP_LR) ? PA_SCROLL_RIGHT : PA_SCROLL_LEFT
            );
        }
    }
}

void AppletMessage::printSerial() {
    Applet::printSerial(); DPRINT(F("\tMessage: ")); DPRINT(message);
    DPRINT(F(", Nb message: ")); DPRINT(messages.size());
    DPRINT(F(", Has messages: ")); DPRINT(hasMessage);
    DPRINT(F(", Timer : ")); DPRINT(timer.getTimeLeft());
    DPRINT(F(", isLoop : ")); DPRINTLN(isLoopMessage);
}

void AppletMessage::addMessage(const char* messageToAdd, uint64_t durationSeconds) {
    if (messages.isFull()) {
        messages.pop();
    }

    MessageLongSettings messageSettings = {
            {'\0'},
            durationSeconds
    };

    strcpy(messageSettings.message, messageToAdd);
//    utf8Ascii(messageSettings.message);

    messages.push(messageSettings);
    hasMessage = true;
}

void AppletMessage::popMessage() {
    MessageLongSettings newMessage = messages.pop();
    DPRINT(F("New message: ")); DPRINTLN(newMessage.message); printSerial();

    strcpy(this->message, newMessage.message);
    timer.setInterval(newMessage.durationSeconds * 1000, true);
    isLoopMessage = newMessage.durationSeconds > 0;
}

void AppletMessage::stopTimer() {
    timer.setExpired();
}