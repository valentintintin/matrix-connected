#ifndef MATRIX_CONNECTED_APPLETMESSAGE_H
#define MATRIX_CONNECTED_APPLETMESSAGE_H

#include <ArduinoQueue.h>

#include "Engine/Applet.h"
#include "Engine/Timer.h"
#include "MessageSettings.h"

#define MAX_MESSAGES 10
#define MAX_LENGTH_MESSAGE 255

class AppletMessage : public Applet {

public:
    explicit AppletMessage(Orchestror *orchestror);

    void stopTimer();

    bool shouldBeResumed(bool animationFinished) override;
    void draw(bool animationFinished) override;
    void printSerial() override;

    bool addMessage(const char* messageToAdd, uint64_t durationSeconds = 0);

private:
    char message[MAX_LENGTH_MESSAGE]{};
    ArduinoQueue<MessageSettings> messages = ArduinoQueue<MessageSettings>(MAX_MESSAGES);
    bool hasMessage = false;
    bool isLoopMessage = false;
    Timer timer = Timer(0);

    void popMessage();
};


#endif //MATRIX_CONNECTED_APPLETMESSAGE_H
