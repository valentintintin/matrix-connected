#ifndef MATRIX_CONNECTED_APPLET_H
#define MATRIX_CONNECTED_APPLET_H

#include <MD_Parola.h>

class Orchestror;

#include "Engine/Utils.h"
#include "Orchestror.h"

#define CLOCK 0
#define HEART 1
#define MESSAGE 2
#define SCREEN_SAVER 3
#define COUNTDOWN 4

class Applet {

public:
    static long APPLET_ID;

    Applet(Orchestror *orchestror, const char* name, const byte type, const byte priority = 0);

    virtual void onInit(MD_Parola *matrix);
    virtual void onPause();
    virtual void onResume(MD_Parola *matrix);
    virtual void onDestroy();

    inline bool isDisplayed() const {
        return displayed;
    }

    const byte getIdZone() const;

    inline const long getId() const {
        return id;
    }

    inline byte getPriority() const {
        return priority;
    }

    inline const char* getName() const {
        return name;
    }

    inline const byte getType() const {
        return type;
    }

    inline const uint16_t getStartColumn() const {
        return startColumn;
    }

    inline const uint16_t getEndColumn() const {
        return endColumn;
    }

    virtual void refresh();
    virtual void printSerial();

    virtual bool shouldBePaused(bool isAnimationFinished) = 0;
    virtual bool shouldBeDestroyed(bool isAnimationFinished) = 0;
    virtual void draw(MD_Parola *matrix, bool isAnimationFinished) = 0;

protected:
    Orchestror* orchestror;

private:
    char name[16];
    const byte type;
    const byte priority;
    const long id;
    bool displayed = false;
    uint16_t startColumn, endColumn;
};


#endif //MATRIX_CONNECTED_APPLET_H
