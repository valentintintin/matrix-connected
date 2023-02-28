#include <NonBlockingRtttl.h>
#include <Time.h>
#include <NtpClientLib.h>
#include "System.h"
#include "FontData.h"

#include "Applets/AppletMessage.h"
#include "Applets/AppletCountdown.h"
#include "Applets/AppletClock.h"
#include "Applets/AppletHeart.h"
#include "Applets/AppletCar.h"
#include "Applets/AppletScreenSaver.h"
#include "Applets/AppletStaticSymbols.h"

System::System(MD_Parola *matrix, byte numDevices, bool enableDong, byte soundPin, byte ledPin, bool resetDisplay, byte mainZone) :
        matrix(matrix), soundPin(soundPin), enableDong(enableDong), hasDong(false),
        mainZone(mainZone), ledPin(ledPin), resetDisplay(resetDisplay), timerRefreshDisplay(INTERVAL_REFRESH_DISPLAY, true) {
    if (soundPin != 255) {
        pinMode(soundPin, OUTPUT);
    }

    if (ledPin != 255) {
        pinMode(ledPin, OUTPUT);
    }

    matrix->begin(NB_MAX_ORCHESTROR);
    matrix->setFont(font);

#ifdef VALENTIN
    matrix->setZone(ZONE_MAIN, 0, 8);
    matrix->setZone(ZONE_CLOCK, 9, 13);
    matrix->setZone(ZONE_HEART, 14, 15);
#elif defined(WILLYAM)
    matrix->setZone(ZONE_MAIN, 0, 5);
    matrix->setZone(ZONE_SYMBOL, 6, 7);
#else
    matrix->setZone(ZONE_MAIN, 0, numDevices - 1);
#endif

    orchestrors[ZONE_MAIN] = new Orchestror(this, (byte) ZONE_MAIN);
    orchestrors[ZONE_MAIN]->addApplet(new AppletMessage(orchestrors[ZONE_MAIN]));
    orchestrors[ZONE_MAIN]->addApplet(new AppletCountdown(orchestrors[ZONE_MAIN]));

#ifdef VALENTIN
    orchestrors[ZONE_MAIN]->addApplet(new AppletScreenSaver(orchestrors[ZONE_MAIN]));

    orchestrors[ZONE_HEART] = new Orchestror(this, (byte) ZONE_HEART);
    orchestrors[ZONE_HEART]->addApplet(new AppletHeart(orchestrors[ZONE_HEART]));
    orchestrors[ZONE_HEART]->addApplet(new AppletStaticSymbols(orchestrors[ZONE_HEART], PSTR("HomeAssistant"), homeAssistant));

    orchestrors[ZONE_CLOCK] = new Orchestror(this, ZONE_CLOCK);
    orchestrors[ZONE_CLOCK]->addApplet(new AppletClock(orchestrors[ZONE_CLOCK]));
#elif defined(WILLYAM)
    orchestrors[ZONE_MAIN]->addApplet(new AppletClock(orchestrors[ZONE_MAIN]));

    orchestrors[ZONE_SYMBOL] = new Orchestror(this, ZONE_SYMBOL);
    orchestrors[ZONE_SYMBOL]->addApplet(new AppletCar(orchestrors[ZONE_SYMBOL]));
#elif defined(VALENTIN_SMALL_STATE)
    orchestrors[ZONE_MAIN]->addApplet(new AppletStaticSymbols(orchestrors[ZONE_MAIN], PSTR("HomeAssistant"), homeAssistant));

    matrix->setZoneEffect(ZONE_MAIN, true, PA_FLIP_UD);
    matrix->setZoneEffect(ZONE_MAIN, true, PA_FLIP_LR);
#elif defined(VALENTIN_SMALL)
    orchestrors[ZONE_MAIN]->addApplet(new AppletClock(orchestrors[ZONE_MAIN]));
    orchestrors[ZONE_MAIN]->addApplet(new AppletStaticSymbols(orchestrors[ZONE_MAIN], PSTR("HomeAssistant"), homeAssistant));
#else
    orchestrors[ZONE_MAIN]->addApplet(new AppletClock(orchestrors[ZONE_MAIN]));
#endif

    setMatrixIntensity(INTENSITY);
    setMatrixActivated(true);
}

void System::setMatrixActivated(bool activated) {
    matrixActivated = activated;

    matrix->displayShutdown(!matrixActivated);

    if (!activated && rtttl::isPlaying()) {
        rtttl::stop();
    }
}

void System::setMatrixIntensity(byte intensity) {
    matrix->setIntensity(intensity);
    matrixIntensity = intensity;
}

void System::update() {
    if (isMatrixActivated()) {
        matrix->displayAnimate();

        for (auto orchestror : orchestrors) {
            if (orchestror->shouldBeDisplayed()) {
                orchestror->update();
            }
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
        // fake delay for avoid CPU stress
        delay(matrix->getSpeed());
    }

    if (resetDisplay && isMatrixActivated() && timerRefreshDisplay.hasExpired()) {
        DPRINTLN(F("[System]resetDisplay"));

        matrix->displayShutdown(true);
        delay(10);
        matrix->displayShutdown(false);

        timerRefreshDisplay.restart();
    }

#ifdef DEBUG
    DPRINT(F("[System]Heap: ")); DPRINTLN(ESP.getFreeHeap());
#endif
}

bool System::setSongToPlay(const char *song) {
    if (soundPin != 255 && rtttl::done()) {
        strcpy_P(bufferSong, song);
        rtttl::begin(soundPin, bufferSong);

        return true;
    }

    return false;
}

bool System::setLed(bool status) const {
    if (ledPin != 255) {
        digitalWrite(ledPin, status);

        return true;
    }

    return false;
}

bool System::setBlink() {
    if (ledPin != 255) {
        setLed(LOW);
        blinkCounter = 0;
        blinkTicker.attach_ms(300, [this] {
            this->blinkProcess();
        });

        return true;
    }

    return false;
}

void System::blinkProcess() {
    digitalWrite(ledPin, !digitalRead(ledPin));

    ++blinkCounter;
    if (blinkCounter == 10) {
        blinkTicker.detach();
        blinkTicker.attach_ms(100, [this] {
            this->blinkProcess();
        });
    } else if (blinkCounter == 30) {
        blinkTicker.detach();
        setLed(LOW);
    }
}

bool System::addMessage(const char* messageToAdd) {
    AppletMessage* applet = (AppletMessage*) getAppletByTypeOnAnyOrchestor(MESSAGE);

    if (applet == nullptr) {
        return false;
    }

    applet->addMessage(messageToAdd);

    return true;
}

bool System::notify() {
    setBlink();
    return setSongToPlay(dangoSong);
}

bool System::dong() {
    setBlink();
    return setSongToPlay(dongSong);
}

bool System::alert() {
    setBlink();
    return setSongToPlay(alertSong);
}

bool System::showDateMessage() {
    time_t moment = now();

    dayStr[0] = '\0';
    strcpy_P(dayStr, (char*) pgm_read_dword(&(weekDays[weekday(moment) - 1])));
    sprintf_P(dateStr, PSTR("Date : %s %02d/%02d/%4d"), dayStr, day(moment), month(moment), year(moment));

    return addMessage(dateStr);
}

Applet *System::getAppletByTypeOnAnyOrchestor(int appletType) {
    for (auto orchestror : orchestrors) {
        if (orchestror == nullptr) {
            continue;
        }

        Applet *applet = orchestror->getAppletByType(appletType);

        if (applet != nullptr) {
            return applet;
        }
    }

    return nullptr;
}
