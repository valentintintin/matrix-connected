#include "AppletScreenSaver.h"

AppletScreenSaver::AppletScreenSaver(Orchestror* orchestror) : Applet(orchestror, PSTR("ScreenSaver")), timer(25, true) {
}

AppletScreenSaver::~AppletScreenSaver() = default;

void AppletScreenSaver::onInit(MD_Parola *matrix) {
    Applet::onInit(matrix);

    currentRow = 0;
    currentColumn = getStartColumn();

    resetToGo();
}

bool AppletScreenSaver::shouldBePaused(bool isAnimationFinished) {
    return false;
}

bool AppletScreenSaver::shouldBeDestroyed(bool isAnimationFinished) {
    return false;
}

void AppletScreenSaver::draw(MD_Parola *matrix, bool isAnimationFinished) {
    if (timer.hasExpired()) {
        timer.restart();

        if (currentRow == toGoRow && currentColumn == toGoColumn) {
            resetToGo();
            matrix->displayClear(getIdZone());
            matrix->getGraphicObject()->setPoint(toGoRow, toGoColumn, true);
        }

        matrix->getGraphicObject()->setPoint(currentRow, currentColumn, true);

        if (currentRow < toGoRow) {
            currentRow++;
        } else if (currentRow > toGoRow) {
            currentRow--;
        } else if (currentColumn < toGoColumn) {
            currentColumn++;
        } else if (currentColumn > toGoColumn) {
            currentColumn--;
        }
    }
}

void AppletScreenSaver::resetToGo() {
    toGoRow = random(0, 8);
    toGoColumn = random(getStartColumn(), getEndColumn());
}
