#ifndef SLIDE_MESSAGE_H
#define SLIDE_MESSAGE_H

#include "Engine/Slide.h"

class SlideMessage : public Slide {

public:
    explicit SlideMessage(Screen *screen, const String &message, byte nbLoop = 0);

    bool shouldRecreate() override;

    ~SlideMessage();

    String getText() override;

    bool isFinished() override;

    void showRaw() {};

protected:
    String message;
    byte nbLoop = 3;
};

#endif
