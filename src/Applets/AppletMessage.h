#ifndef MATRIX_CONNECTED_APPLETMESSAGE_H
#define MATRIX_CONNECTED_APPLETMESSAGE_H

#include <CircularBuffer.h>

#include "Engine/Applet.h"
#include "Engine/Timer.h"
#include "MessageSettings.h"

#define MAX_MESSAGES 10

class AppletMessage : public Applet {

public:
    explicit AppletMessage(Orchestror *orchestror);

    void stopTimer();

    bool shouldBeResumed(bool animationFinished) override;
    void draw(bool animationFinished) override;
    void printSerial() override;

    void addMessage(const char* messageToAdd, unsigned long durationSeconds = 0);

private:
    char message[MAX_LENGTH_MESSAGE]{};
    CircularBuffer<MessageLongSettings, MAX_MESSAGES> messages;

    bool hasMessage = false;
    bool isLoopMessage = false;
    Timer timer = Timer(0);

    void popMessage();
};


#endif //MATRIX_CONNECTED_APPLETMESSAGE_H
