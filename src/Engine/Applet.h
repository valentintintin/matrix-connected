#ifndef MATRIX_CONNECTED_APPLET_H
#define MATRIX_CONNECTED_APPLET_H

#include <MD_Parola.h>

#include "Engine/Utils.h"

class Applet {

public:
    Applet(byte idZone, const char* name, byte priority = 0);
    ~Applet();

    void onInit();
    void onPause();
    void OnResume();
    void onDestroy();

    inline bool isDisplayed() const {
        return displayed;
    }

    inline byte getIdZone() const {
        return idZone;
    }

    inline byte getPriority() const {
        return priority;
    }

    inline const char* getName() const {
        return name;
    }

    virtual void refresh();
    virtual void printSerial();

    virtual bool shouldBePaused(bool isAnimationFinished) = 0;
    virtual bool shouldBeDestroyed(bool isAnimationFinished) = 0;
    virtual void draw(MD_Parola* matrix, bool isAnimationFinished) = 0;

private:
    char name[16];
    const byte idZone;
    const byte priority;
    bool displayed = false;
};


#endif //MATRIX_CONNECTED_APPLET_H
