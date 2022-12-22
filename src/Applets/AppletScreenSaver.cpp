#include "AppletScreenSaver.h"

AppletScreenSaver::AppletScreenSaver(Orchestror* orchestror) : Applet(orchestror, PSTR("ScreenSaver"), SCREEN_SAVER), timer(25, true) {
}

void AppletScreenSaver::onInit(MD_Parola *matrix) {
    Applet::onInit(matrix);

    currentRow = 4;
    currentColumn = (getEndColumn() - getStartColumn()) / 2 + getStartColumn();

    resetToGo();
}

bool AppletScreenSaver::shouldBeResumed() {
    return true;
}

bool AppletScreenSaver::shouldBeDestroyed() {
    return false;
}

void AppletScreenSaver::draw(MD_Parola *matrix) {
    if (timer.hasExpired()) {
        timer.restart();

        if (currentRow == toGoRow && currentColumn == toGoColumn) {
            resetToGo();
            matrix->displayClear(getIdZone());
            matrix->getGraphicObject()->setPoint(toGoRow, toGoColumn, true);
        }

        matrix->getGraphicObject()->setPoint(currentRow, currentColumn, true);

        if (moveDiagonal) {
            doMoveDiagonal();
        } else {
            doMoveNoDiagonal();
        }
    }
}

void AppletScreenSaver::resetToGo() {
    moveDiagonal = random(0, 2) == 0;
    toGoRow = random(0, 8);
    toGoColumn = random(
        toGoColumn - MAX_COLUMN_AWAY > getStartColumn() ? toGoColumn - MAX_COLUMN_AWAY : getStartColumn(),
        toGoColumn + MAX_COLUMN_AWAY < getEndColumn() ? toGoColumn + MAX_COLUMN_AWAY : getEndColumn()
    );
}

void AppletScreenSaver::doMoveNoDiagonal() {
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

void AppletScreenSaver::doMoveDiagonal() {
    if (currentRow < toGoRow) {
        currentRow++;
    } else if (currentRow > toGoRow) {
        currentRow--;
    }

    if (currentColumn < toGoColumn) {
        currentColumn++;
    } else if (currentColumn > toGoColumn) {
        currentColumn--;
    }
}