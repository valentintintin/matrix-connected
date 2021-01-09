#ifndef APPLET_TIMER_H
#define APPLET_TIMER_H

#include "../../old/Applet.h"

class AppletTimer : public Applet {

public:
    explicit AppletTimer(Screen *screen);

    ~AppletTimer();

    String getText() override;

    bool isFinished() override;

    void start();

    bool shouldRecreate() override;

    void restart();

    void stop();

    void showRaw() {};

private:
    bool running = false;
    uint64_t initTime, lastTime;
    String timeString;
};

#endif
