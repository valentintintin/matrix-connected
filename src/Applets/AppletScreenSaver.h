#ifndef MATRIX_CONNECTED_APPLETSCREENSAVER_H
#define MATRIX_CONNECTED_APPLETSCREENSAVER_H

#include "../Engine/Applet.h"
#include "../Engine/Timer.h"

#define MAX_COLUMN_AWAY 24

class AppletScreenSaver : public Applet {

public:
    explicit AppletScreenSaver(Orchestror* orchestror);

    void onInit() override;

    bool shouldBeResumed(bool animationFinished) override;
    void draw(bool animationFinished) override;
    void doMoveDiagonal();
    void doMoveNoDiagonal();

private:
    void resetToGo();

    Timer timer;
    bool moveDiagonal = false;
    uint16_t toGoColumn{}, toGoRow{};
    uint16_t currentRow{}, currentColumn{};
};


#endif //MATRIX_CONNECTED_APPLETSCREENSAVER_H
