#include <Engine/Utils.h>
#include "Engine/Slide.h"
#include "SlideMessage.h"

SlideMessage::SlideMessage(Screen *screen, const String &message, byte nbLoop) : Slide(screen), message(message),
                                                                                 nbLoop(nbLoop) {
    utf8ToCp437(this->message);
    if (this->message.length() * 6 < (uint16_t) screen->matrix.width()) {
        textEffect = _PRINT;
    }
    create();
}

String SlideMessage::getText() {
    return message;
}

SlideMessage::~SlideMessage() {
}

bool SlideMessage::isFinished() {
    if (nbLoop > 0) {
        if (baseIsFinished()) {
            zone.Reset();
            nbLoop--;
            timer.restart();
        }
        return false;
    }
    return baseIsFinished();
}

bool SlideMessage::shouldRecreate() {
    return false;
}

