#include "Screen.h"
#include "Applet.h"

#include <NonBlockingRtttl.h>

Screen::Screen(byte csPin, byte hDisplays, byte soundPin, byte ledPin) : /*matrix(PPMax72xxPanel(csPin, hDisplays, 1)),old*/
                                                                         soundPin(soundPin), ledPin(ledPin) {
    if (soundPin != 255) {
        pinMode(soundPin, OUTPUT);
    }
    if (ledPin != 255) {
        pinMode(ledPin, OUTPUT);
    }

//    matrix.setRotation(0, 3);
//    matrix.setRotation(1, 3);
//    matrix.setRotation(2, 3);
//    matrix.setRotation(3, 3);
//    matrix.setRotation(4, 3);
//    matrix.setRotation(5, 3);
//    matrix.setRotation(6, 3);
//    matrix.setRotation(7, 3);
//
//    matrix.setCursor(0, 0);
//    matrix.setTextColor(HIGH, LOW);
//    matrix.setTextWrap(false);

    setState(true);
}

void Screen::addApplet(Applet *slide) {
    if (enabled) {
        slides.push(slide);
    } else {
        delete slide;
    }
}

bool Screen::refresh() {
    bool shouldRefresh = false;

//    printApplets();

    if (enabled) {
//        matrix.fillScreen(LOW);

        if (slides.count() > 0) {
            auto *slide = slides.peek();
            shouldRefresh = slide->show();
            if (slide->isFinished()) {
                slides.pop();
                delete slide;
                if (slides.count() > 0) {
                    slides.peek()->create();
                }
            }
        } else if (mainApplet != nullptr) {
            if (mainApplet->isFinished()) {
                if (mainApplet->shouldRecreate()) {
                    mainApplet->create();
                } else if (fallBackApplet != nullptr) {
                    mainApplet = fallBackApplet;
                    mainApplet->create();
                } else {
                    mainApplet = nullptr;
                }
            }
            shouldRefresh = mainApplet != nullptr ? mainApplet->show() : true;
        }

        if (shouldRefresh) {
//            matrix.write();
            delay(10);
        }

//        if (!rtttl::done()) {
//            rtttl::play();
//        }
    }

    return shouldRefresh;
}

void Screen::setMainApplet(Applet *slide) {
    if (slide == nullptr && fallBackApplet != nullptr) {
        mainApplet = fallBackApplet;
    } else {
        mainApplet = slide;
    }
}

const Applet *Screen::getMainApplet() {
    return mainApplet;
}

void Screen::setState(bool on) {
//    if (!on && rtttl::isPlaying()) {
//        rtttl::stop();
//    }
    if ((!on && enabled) || (!enabled && on)) {
//        matrix.setIntensity(intensity);
//        matrix.fillScreen(LOW);
//        matrix.write();
    }
    enabled = on;
}

void Screen::setIntensity(byte intensity) {
	this->intensity = intensity;
	if (enabled) {
//		matrix.setIntensity(intensity);
	}
}

void Screen::setFallBackApplet(Applet *slide) {
    fallBackApplet = slide;
    if (mainApplet == nullptr) {
        mainApplet = slide;
    }
}

void Screen::printApplets() {
    Serial.print(F("Applets :"));
    Serial.print(F("\tQueue : "));
    Serial.println(slides.count());
    if (slides.count() > 0) {
        Serial.print(F("Queue front : "));
        slides.peek()->print();
    }
    if (mainApplet != nullptr) {
        Serial.print(F("Main : "));
        mainApplet->print();
    }
    if (fallBackApplet != nullptr) {
        Serial.print(F("FallBack : "));
        fallBackApplet->print();
    }
    Serial.print(F("Enabled :"));
    Serial.println(enabled);
    Serial.print(F("RAM :"));
    Serial.println(ESP.getFreeHeap());
}

void Screen::setSongToPlay(const char *song) {
    if (soundPin != 255) {
        rtttl::begin(soundPin, song);
    }
}

void Screen::setLed(bool status) {
    if (ledPin != 255) {
        digitalWrite(ledPin, status);
    }
}

void Screen::setBlink() {
//    if (ledPin != 255) {
//        setLed(false);
//        blinkCounter = 0;
//        blinkTicker.attach(0.3, [this]() {
//            this->blinkProcess();
//        });
//    }
}

void Screen::blinkProcess() {
//    digitalWrite(ledPin, !digitalRead(ledPin));
//
//    ++blinkCounter;
//    if (blinkCounter == 10) {
//        blinkTicker.attach(0.1, [this]() {
//            this->blinkProcess();
//        });
//    } else if (blinkCounter == 30) {
//        blinkTicker.detach();
//        digitalWrite(ledPin, LOW);
//    }
}
