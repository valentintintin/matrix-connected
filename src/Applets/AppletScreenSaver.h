#ifndef MATRIX_CONNECTED_APPLETSCREENSAVER_H
#define MATRIX_CONNECTED_APPLETSCREENSAVER_H

#include "../Engine/Applet.h"
#include "../Engine/Timer.h"

#define MAX_COLUMN_AWAY 24

class AppletScreenSaver : public Applet {

public:
    explicit AppletScreenSaver(Orchestror* orchestror);
    ~AppletScreenSaver();

    void onInit(MD_Parola* matrix) override;

    bool shouldBePaused(bool isAnimationFinished) override;
    bool shouldBeDestroyed(bool isAnimationFinished) override;
    void draw(MD_Parola *matrix, bool isAnimationFinished) override;

private:
    void resetToGo();

    Timer timer;
    uint16_t toGoColumn, toGoRow;
    uint16_t currentRow, currentColumn;
};


#endif //MATRIX_CONNECTED_APPLETSCREENSAVER_H
