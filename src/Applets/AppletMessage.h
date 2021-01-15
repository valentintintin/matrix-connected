#ifndef MATRIX_CONNECTED_APPLETMESSAGE_H
#define MATRIX_CONNECTED_APPLETMESSAGE_H

#include "../Engine/Applet.h"

#define MAX_LENGTH_MESSAGE 255

class AppletMessage : public Applet {

public:
    explicit AppletMessage(Orchestror* orchestror, byte idZone, String message);
    ~AppletMessage();

    bool shouldBePaused(bool isAnimationFinished) override;
    bool shouldBeDestroyed(bool isAnimationFinished) override;
    void draw(MD_Parola *matrix, bool isAnimationFinished) override;
    void printSerial() override;

private:
    char message[MAX_LENGTH_MESSAGE];
};


#endif //MATRIX_CONNECTED_APPLETMESSAGE_H
