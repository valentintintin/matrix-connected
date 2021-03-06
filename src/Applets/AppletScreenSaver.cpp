#include "AppletScreenSaver.h"

AppletScreenSaver::AppletScreenSaver(Orchestror* orchestror) : Applet(orchestror, PSTR("ScreenSaver"), SCREEN_SAVER), timer(25, true) {
}

void AppletScreenSaver::onInit(MD_Parola *matrix) {
    Applet::onInit(matrix);

    currentRow = 4;
    currentColumn = (getEndColumn() - getStartColumn()) / 2 + getStartColumn();

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
    toGoColumn = random(
        toGoColumn - MAX_COLUMN_AWAY > getStartColumn() ? toGoColumn - MAX_COLUMN_AWAY : getStartColumn(),
        toGoColumn + MAX_COLUMN_AWAY < getEndColumn() ? toGoColumn + MAX_COLUMN_AWAY : getEndColumn()
    );
}
