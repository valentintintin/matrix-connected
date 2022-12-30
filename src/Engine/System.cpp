#include <NonBlockingRtttl.h>
#include <Time.h>
#include <NtpClientLib.h>
#include "System.h"
#include "FontData.h"

#include "Applets/AppletMessage.h"
#include "Applets/AppletClock.h"

System::System(MD_Parola *matrix, byte numDevices, bool enableDong, byte soundPin, byte ledPin, byte mainZone) :
    matrix(matrix), soundPin(soundPin), enableDong(enableDong), hasDong(false),
    mainZone(mainZone), ledPin(ledPin), blinkTicker(new Ticker()),
    numDevices(numDevices), timerPingPixelServer(INTERVAL_PING_PIXEL_SERVER, true) {
    wifiClient.setInsecure();

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
    orchestrors[ZONE]->addApplet(new AppletClock(orchestrors[ZONE], numDevices > 4));
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
        // fake delay for avoid CPU stress
        delay(matrix->getSpeed());
    }

    if (timerPingPixelServer.hasExpired()) {
        pingPixelServer();
        timerPingPixelServer.restart();
    }

#ifdef DEBUG
    delay(75);
    Serial.print(F("Heap: ")); Serial.println(ESP.getFreeHeap());
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
        blinkTicker->attach_ms(300, [this] {
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
        blinkTicker->detach();
        blinkTicker->attach_ms(100, [this] {
            this->blinkProcess();
        });
    } else if (blinkCounter == 30) {
        blinkTicker->detach();
        setLed(LOW);
    }
}

bool System::addMessage(const char* messageToAdd) {
    Applet* applet = getAppletByTypeOnAnyOrchestor(MESSAGE);

    if (applet == nullptr) {
        return false;
    }

    ((AppletMessage*) applet)->addMessage(messageToAdd);

    return true;
}

bool System::notify() {
    DPRINTLN(F("[SYSTEM]Notify"));
    setBlink();
    return setSongToPlay(dangoSong);
}

bool System::dong() {
    DPRINTLN(F("[SYSTEM]Dong"));
    setBlink();
    return setSongToPlay(dongSong);
}

bool System::alert() {
    DPRINTLN(F("[SYSTEM]Alert"));
    setBlink();
    return setSongToPlay(alertSong);
}

bool System::showDateMessage() {
    time_t moment = now();

    dayStr[0] = '\0';
    strcpy_P(dayStr, (char*) pgm_read_dword(&(weekDays[weekday(moment) - 1])));
    sprintf_P(dateStr, PSTR("On est le %s %02d/%02d/%4d"), dayStr, day(moment), month(moment), year(moment));

    return addMessage(dateStr);
}

bool System::pingPixelServer() {
    DPRINTLN(F("[System]pingPixelServer"));

    http.begin(wifiClient, F("http://pixel-server.ovh/esp_clock/index.php"));
    http.addHeader(F("Content-Type"), F("application/x-www-form-urlencoded"));

    rst_info *resetInfo = ESP.getResetInfoPtr();
    sprintf_P(pingPixelServerPayload, PSTR("name=%s&uptime=%ld&restartReason=%d"), F(AP_SSID), NTP.getUptime(), resetInfo->reason);

    DPRINT(F("[System]pingPixelServer payload: ")); DPRINTLN(pingPixelServerPayload);

    int successCode = http.POST(pingPixelServerPayload);

    if (successCode <= 0) {
        DPRINT(F("[System]pingPixelServer: Error code ")); DPRINTLN(http.errorToString(successCode));
    } else {
        DPRINT(F("[System]pingPixelServer: ")); DPRINTLN(http.getString());
    }

    http.end();

    delay(5000);

    return successCode > 0;
}

void System::shouldPingPixelServer() {
    timerPingPixelServer.setExpired();
}

Applet *System::getAppletByTypeOnAnyOrchestor(int appletType) {
    for (auto orchestror : orchestrors) {
        for (byte i = 0; i < NB_MAX_APPLETS; i++) {
            Applet *applet = orchestror->getAppletByType(appletType);

            if (applet != nullptr) {
                return applet;
            }
        }
    }

    return nullptr;
}
