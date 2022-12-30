#ifndef MATRIX_CONNECTED_APPLETSCREENSAVER_H
#define MATRIX_CONNECTED_APPLETSCREENSAVER_H

#include "../Engine/Applet.h"
#include "../Engine/Timer.h"

#define MAX_COLUMN_AWAY 24

class AppletScreenSaver : public Applet {

public:
    explicit AppletScreenSaver(Orchestror* orchestror);

    void onInit(MD_Parola* matrix) override;

    bool shouldBeResumed() override;
    bool shouldBeDestroyed() override;
    void draw(MD_Parola *matrix) override;
    void doMoveDiagonal();
    void doMoveNoDiagonal();

private:
    void resetToGo();

    Timer timer;
    bool moveDiagonal = false;
    uint16_t toGoColumn, toGoRow;
    uint16_t currentRow, currentColumn;
};


#endif //MATRIX_CONNECTED_APPLETSCREENSAVER_H
