#ifndef MATRIX_CONNECTED_APPLETMESSAGE_H
#define MATRIX_CONNECTED_APPLETMESSAGE_H

#include <ArduinoQueue.h>

#include "Engine/Applet.h"

#define MAX_MESSAGES 15
#define MAX_LENGTH_MESSAGE 255

class AppletMessage : public Applet {

public:
    explicit AppletMessage(Orchestror *orchestror);

    bool shouldBeResumed(bool animationFinished) override;
    bool shouldBeDestroyed(bool animationFinished) override;
    void draw(bool animationFinished) override;
    void printSerial() override;

    bool addMessage(const char* messageToAdd);

private:
    char message[MAX_LENGTH_MESSAGE]{};
    ArduinoQueue<char*> messages = ArduinoQueue<char*>(MAX_MESSAGES);
    bool hasMessage = false;

    void popMessage();
};


#endif //MATRIX_CONNECTED_APPLETMESSAGE_H
