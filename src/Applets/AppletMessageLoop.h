#ifndef MATRIX_CONNECTED_APPLETMESSAGELOOP_H
#define MATRIX_CONNECTED_APPLETMESSAGELOOP_H

#include "Engine/Applet.h"
#include "../Engine/Timer.h"

#define MAX_LENGTH_MESSAGE 255

class AppletMessageLoop : public Applet {

public:
    explicit AppletMessageLoop(Orchestror *orchestror, const char* messageToAdd, uint64_t secondToCount);

    bool shouldBeResumed() override;
    bool shouldBeDestroyed() override;
    void draw(bool animationFinished) override;
    void printSerial() override;
    void stopTimer();

private:
    char message[MAX_LENGTH_MESSAGE]{};
    Timer timer;
};


#endif //MATRIX_CONNECTED_APPLETMESSAGELOOP_H
