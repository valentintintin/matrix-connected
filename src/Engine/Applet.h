#ifndef MATRIX_CONNECTED_APPLET_H
#define MATRIX_CONNECTED_APPLET_H

#include <MD_Parola.h>

class Orchestror;

#include "Engine/Utils.h"
#include "Orchestror.h"

#define CLOCK 0
#define SYMBOLS_ANIMATED 1
#define MESSAGE 2
#define SCREEN_SAVER 3
#define COUNTDOWN 4
#define MESSAGE_LOOP 5
#define STATIC_SYMBOLS 6

class Applet {

public:
    static long APPLET_ID;

    Applet(Orchestror *orchestror, const char* name, byte type, byte priority = 0);

    virtual void onInit();
    virtual void onPause();
    virtual void onResume();

    inline bool isDisplayed() const {
        return displayed;
    }

    byte getIdZone() const;
    MD_Parola* getMatrix() const;

    inline long getId() const {
        return id;
    }

    virtual inline byte getPriority() const {
        return priority;
    }

    inline const char* getName() const {
        return name;
    }

    inline byte getType() const {
        return type;
    }

    uint16_t getStartColumn() const {
        return startColumn;
    }

    uint16_t getEndColumn() const {
        return endColumn;
    }

    uint16_t getNumberColumns() const {
        return getEndColumn() - getStartColumn() + 1;
    }

    virtual void refresh();
    virtual void printSerial();

    virtual bool shouldBeResumed(bool animationFinished) = 0;
    virtual void draw(bool animationFinished) = 0;

protected:
    Orchestror* orchestror;

private:
    char name[16]{};
    const byte type;
    const byte priority;
    const long id;
    bool displayed = false;
    uint16_t startColumn{}, endColumn{};
};


#endif //MATRIX_CONNECTED_APPLET_H
