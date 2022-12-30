#ifndef MATRIX_CONNECTED_APPLETMESSAGE_H
#define MATRIX_CONNECTED_APPLETMESSAGE_H

#include <Queue.h>

#include "Engine/Applet.h"

#define MAX_MESSAGES 15
#define MAX_LENGTH_MESSAGE 255

class AppletMessage : public Applet {

public:
    explicit AppletMessage(Orchestror *orchestror);

    bool shouldBeResumed() override;
    bool shouldBeDestroyed() override;
    void draw(MD_Parola *matrix) override;
    void printSerial() override;

    void addMessage(const char* messageToAdd);

private:
    char message[MAX_LENGTH_MESSAGE]{};
    Queue<char*> messages = Queue<char*>(MAX_MESSAGES);
    bool hasMessage = false;

    void popMessage();
};


#endif //MATRIX_CONNECTED_APPLETMESSAGE_H
