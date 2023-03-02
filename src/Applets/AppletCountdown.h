#ifndef APPLET_COUNTDOWN_H
#define APPLET_COUNTDOWN_H

#include "Engine/Applet.h"
#include "MessageSettings.h"

#define MESSAGE_RECALL_MS_SECOND 240000 // every 4 minutes
#define PRIORITY_MAX_BELLOW_MS_SECOND 180000 // 3 minutes

class AppletCountdown : public Applet {

public:
    AppletCountdown(Orchestror *orchestror);

    void startTimer(unsigned long secondToCount, const char* name = nullptr);
    void stopTimer(bool withEnd = true);

    bool shouldBeResumed(bool animationFinished) override;
    void refresh() override;
    void draw(bool animationFinished) override;
    void printSerial() override;
    byte getPriority() const override;

    inline bool currentlyRunning() const {
        return isRunning;
    }

    Timer timer = Timer();
private:
    bool isRunning = false;

    char timeStr[32]{};
    char name[MAX_LENGTH_MESSAGE]{};
    char buffer[MAX_LENGTH_MESSAGE + 32]{};

    bool withThirdData;
};

#endif
