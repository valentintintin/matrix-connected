#ifndef MATRIX_CONNECTED_APPLETMESSAGE_H
#define MATRIX_CONNECTED_APPLETMESSAGE_H

#include <Queue.h>

#include "Engine/Applet.h"

#define MAX_MESSAGES 15
#define MAX_LENGTH_MESSAGE 255

class AppletMessage : public Applet {

public:
    explicit AppletMessage(Orchestror *orchestror);
    ~AppletMessage();

    void onResume(MD_Parola *matrix) override;
    bool shouldBePaused(bool isAnimationFinished) override;
    bool shouldBeDestroyed(bool isAnimationFinished) override;
    void draw(MD_Parola *matrix, bool isAnimationFinished) override;
    void printSerial() override;

    void addMessage(String messageToAdd);

private:
    char message[MAX_LENGTH_MESSAGE];
    Queue<char*> messages = Queue<char*>(MAX_MESSAGES);
};


#endif //MATRIX_CONNECTED_APPLETMESSAGE_H
