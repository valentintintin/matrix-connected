#include <NonBlockingRtttl.h>
#include <Time.h>
#include <NtpClientLib.h>
#include "System.h"
#include "FontData.h"

#include "Applets/AppletHeart.h"
#include "Applets/AppletScreenSaver.h"
#include "Applets/AppletMessage.h"
#include "Applets/AppletClock.h"

System::System(MD_Parola *matrix, bool enableDong, byte soundPin, byte ledPin) :
    matrix(matrix), soundPin(soundPin), enableDong(enableDong), hasDong(false), ledPin(ledPin), blinkTicker(new Ticker()) {
    DPRINTLN(F("[MATRIX]Start"));

    if (soundPin != 255) {
        pinMode(soundPin, OUTPUT);
    }

    if (ledPin != 255) {
        pinMode(ledPin, OUTPUT);
    }

    matrix->begin(NB_MAX_ORCHESTROR);
    matrix->setZone(ZONE, 0, 7);
    setMatrixIntensity(1);
    matrix->setFont(font);
    setMatrixActivated(true);

    orchestrors[ZONE] = new Orchestror(this, (byte) ZONE);

    DPRINT(F("[ORCHESTROR]")); DPRINT(NB_MAX_APPLETS); DPRINTLN(F(" applets max"));
    orchestrors[ZONE]->addApplet(new AppletClock(orchestrors[ZONE]));
    orchestrors[ZONE]->addApplet(new AppletMessage(orchestrors[ZONE]));
}

void System::setMatrixActivated(bool activated) {
    DPRINTLN(F("[ORCHESTROR]Change matrixActivated to ")); DPRINTLN(matrixActivated);

    matrixActivated = activated;

    matrix->displayShutdown(!matrixActivated);

    if (!activated && rtttl::isPlaying()) {
        rtttl::stop();
    }
}

void System::setMatrixIntensity(byte intensity) {
    matrix->setIntensity(matrixIntensity);
    matrixIntensity = intensity;
}

void System::update() {
    DPRINT(F("[SYSTEM]MatrixActivated: ")); DPRINT(isMatrixActivated()); DPRINTLN(F("]\r\n\t[UPDATE]"));

    if (isMatrixActivated()) {
        matrix->displayAnimate();

        for (auto orchestror : orchestrors) {
            orchestror->update();
        }

        time_t currentTime = now();
        if (enableDong && minute(currentTime) == 0 && second(currentTime) == 0) {
            if (!hasDong) {
                dong();
                showDateMessage();
                hasDong = true;
            }
        } else {
            hasDong = false;
        }

        if (rtttl::isPlaying()) {
            rtttl::play();
        }
    } else {
        // fake delay for CPU stress
        delay(matrix->getSpeed());
    }
}

void System::setSongToPlay(const char *song) {
    if (soundPin != 255 && rtttl::done()) {
        strcpy_P(bufferSong, song);
        rtttl::begin(soundPin, bufferSong);
    }
}

void System::setLed(bool status) const {
    if (ledPin != 255) {
        digitalWrite(ledPin, status);
    }
}

void System::setBlink() {
    if (ledPin != 255) {
        setLed(LOW);
        blinkCounter = 0;
        blinkTicker->attach_ms(300, [this] {
            this->blinkProcess();
        });
    }
}

void System::blinkProcess() {
    digitalWrite(ledPin, !digitalRead(ledPin));

    ++blinkCounter;
    if (blinkCounter == 10) {
        blinkTicker->detach();
        blinkTicker->attach_ms(100, [this] {
            this->blinkProcess();
        });
    } else if (blinkCounter == 30) {
        blinkTicker->detach();
        setLed(LOW);
    }
}

bool System::addMessage(const String& messageToAdd) {
    Orchestror* orchestror = getOrchestorForZone(ZONE);
    Applet* applet = orchestror->getAppletByType(MESSAGE);

    if (applet == nullptr) {
        return false;
    }

    ((AppletMessage*) applet)->addMessage(messageToAdd);

    return true;
}

bool System::addMessage(const char* messageToAdd) {
    Orchestror* orchestror = getOrchestorForZone(ZONE);
    Applet* applet = orchestror->getAppletByType(MESSAGE);

    if (applet == nullptr) {
        return false;
    }

    ((AppletMessage*) applet)->addMessage(messageToAdd);

    return true;
}

void System::notify() {
    DPRINTLN(F("[SYSTEM]Notify"));
    setSongToPlay(dangoSong);
    setBlink();
}

void System::dong() {
    DPRINTLN(F("[SYSTEM]Dong"));
    setSongToPlay(dongSong);
    setBlink();
}

void System::alert() {
    DPRINTLN(F("[SYSTEM]Alert"));
    setSongToPlay(alertSong);
    setBlink();
}

void System::showDateMessage() {
    time_t moment = now();
    dayStr[0] = '\0';
    strcpy_P(dayStr, (char*) pgm_read_dword(&(weekDays[weekday(moment) - 1])));
    sprintf_P(dateStr, PSTR("On est le %s %02d/%02d/%4d"), dayStr, day(moment), month(moment), year(moment));
    addMessage(dateStr);
}