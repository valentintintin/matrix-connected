#include "AppletScreenSaver.h"

AppletScreenSaver::AppletScreenSaver(Orchestror* orchestror) : Applet(orchestror, PSTR("ScreenSaver"), SCREEN_SAVER), timer(25, true) {
}

void AppletScreenSaver::onInit() {
    Applet::onInit();

    currentRow = 4;
    currentColumn = (getEndColumn() - getStartColumn()) / 2 + getStartColumn();

    resetToGo();
}

bool AppletScreenSaver::shouldBeResumed(bool animationFinished) {
    return true;
}

void AppletScreenSaver::draw(bool animationFinished) {
    if (timer.hasExpired()) {
        timer.restart();

        if (currentRow == toGoRow && currentColumn == toGoColumn) {
            resetToGo();
            getMatrix()->displayClear(getIdZone());
            getMatrix()->getGraphicObject()->setPoint(toGoRow, toGoColumn, !getMatrix()->getInvert());
        }

        getMatrix()->getGraphicObject()->setPoint(currentRow, currentColumn, !getMatrix()->getInvert());

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