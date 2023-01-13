#ifndef APPLET_COUNTDOWN_H
#define APPLET_COUNTDOWN_H

#include "Engine/Applet.h"

#define MAX_LENGTH_MESSAGE 255
#define MESSAGE_RECALL_MS_SECOND 240000 // every 4 minutes
#define PRIORITY_MAX_BELLOW_MS_SECOND MESSAGE_RECALL_MS_SECOND - 30000

class AppletCountdown : public Applet {

public:
    AppletCountdown(Orchestror *orchestror, unsigned long secondToCount, const char* name = nullptr, bool songAtTheEnd = true);

    void stopTimer();

    bool shouldBeResumed(bool animationFinished) override;
    bool shouldBeDestroyed(bool animationFinished) override;
    void refresh() override;
    void draw(bool animationFinished) override;
    void printSerial() override;
    byte getPriority() const override;

    Timer timer;
private:
    bool songAtTheEnd;
    char timeStr[32]{};
    char name[MAX_LENGTH_MESSAGE]{};
    char buffer[MAX_LENGTH_MESSAGE + 16]{};
    bool withThirdData;
};

#endif
