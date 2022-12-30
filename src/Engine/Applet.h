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
#define MESSAGE_LOOP 5

class Applet {

public:
    static long APPLET_ID;

    Applet(Orchestror *orchestror, const char* name, byte type, byte priority = 0);

    virtual void onInit(MD_Parola *matrix);
    virtual void onPause();
    virtual void onResume(MD_Parola *matrix);
    virtual void onDestroy();

    inline bool isDisplayed() const {
        return displayed;
    }

    byte getIdZone() const;

    inline long getId() const {
        return id;
    }

    inline byte getPriority() const {
        return priority;
    }

    inline const char* getName() const {
        return name;
    }

    inline byte getType() const {
        return type;
    }

    inline uint16_t getStartColumn() const {
        return startColumn;
    }

    inline uint16_t getEndColumn() const {
        return endColumn;
    }

    virtual void refresh();
    virtual void printSerial();

    virtual bool shouldBeResumed() = 0;
    virtual bool shouldBeDestroyed() = 0;
    virtual void draw(MD_Parola *matrix) = 0;

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
