#ifndef APPLET_COUNTDOWN_H
#define APPLET_COUNTDOWN_H

#include "Engine/Applet.h"

#define MAX_LENGTH_MESSAGE 255
#define MESSAGE_RECALL_MS_SECOND 240000 // every 4 minutes

class AppletCountdown : public Applet {

public:
    AppletCountdown(Orchestror *orchestror, unsigned long secondToCount, String name = "", bool songAtTheEnd = true);

    void stopTimer(bool forced = false);

    bool shouldBeResumed() override;
    bool shouldBeDestroyed() override;
    void refresh() override;
    void draw(MD_Parola *matrix) override;
    void printSerial() override;

private:
    bool songAtTheEnd;
    Timer timer;
    char timeStr[16]{};
    char name[MAX_LENGTH_MESSAGE]{};
    char buffer[MAX_LENGTH_MESSAGE + 16]{};
};

#endif
