#include "Screen.h"
#include "Slide.h"

#include <NonBlockingRtttl.h>

Screen::Screen(byte csPin, byte hDisplays, byte soundPin, byte ledPin) : matrix(PPMax72xxPanel(csPin, hDisplays, 1)),
                                                                         soundPin(soundPin), ledPin(ledPin) {
    if (soundPin != 255) {
        pinMode(soundPin, OUTPUT);
    }
    if (ledPin != 255) {
        pinMode(ledPin, OUTPUT);
    }

    matrix.setRotation(0, 3);
    matrix.setRotation(1, 3);
    matrix.setRotation(2, 3);
    matrix.setRotation(3, 3);
    matrix.setRotation(4, 3);
    matrix.setRotation(5, 3);
    matrix.setRotation(6, 3);
    matrix.setRotation(7, 3);

    matrix.setCursor(0, 0);
    matrix.setTextColor(HIGH, LOW);
    matrix.setTextWrap(false);

    setState(true);
}

void Screen::addSlide(Slide *slide) {
    if (enabled) {
        slides.push(slide);
    } else {
        delete slide;
    }
}

bool Screen::refresh() {
    bool shouldRefresh = false;

//    printSlides();

    if (enabled) {
        matrix.fillScreen(LOW);

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
        } else if (mainSlide != nullptr) {
            if (mainSlide->isFinished()) {
                if (mainSlide->shouldRecreate()) {
                    mainSlide->create();
                } else if (fallBackSlide != nullptr) {
                    mainSlide = fallBackSlide;
                    mainSlide->create();
                } else {
                    mainSlide = nullptr;
                }
            }
            shouldRefresh = mainSlide != nullptr ? mainSlide->show() : true;
        }

        if (shouldRefresh) {
            matrix.write();
            delay(10);
        }

        if (!rtttl::done()) {
            rtttl::play();
        }
    }

    return shouldRefresh;
}

void Screen::setMainSlide(Slide *slide) {
    if (slide == nullptr && fallBackSlide != nullptr) {
        mainSlide = fallBackSlide;
    } else {
        mainSlide = slide;
    }
}

const Slide *Screen::getMainSlide() {
    return mainSlide;
}

void Screen::setState(bool on) {
    if (!on && rtttl::isPlaying()) {
        rtttl::stop();
    }
    if ((!on && enabled) || (!enabled && on)) {
        matrix.setIntensity(intensity);
        matrix.fillScreen(LOW);
        matrix.write();
    }
    enabled = on;
}

void Screen::setIntensity(byte intensity) {
	this->intensity = intensity;
	if (enabled) {
		matrix.setIntensity(intensity);
	}
}

void Screen::setFallBackSlide(Slide *slide) {
    fallBackSlide = slide;
    if (mainSlide == nullptr) {
        mainSlide = slide;
    }
}

void Screen::printSlides() {
    Serial.print(F("Slides :"));
    Serial.print(F("\tQueue : "));
    Serial.println(slides.count());
    if (slides.count() > 0) {
        Serial.print(F("Queue front : "));
        slides.peek()->print();
    }
    if (mainSlide != nullptr) {
        Serial.print(F("Main : "));
        mainSlide->print();
    }
    if (fallBackSlide != nullptr) {
        Serial.print(F("FallBack : "));
        fallBackSlide->print();
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
    if (ledPin != 255) {
        setLed(false);
        blinkCounter = 0;
        blinkTicker.attach(0.3, [this]() {
            this->blinkProcess();
        });
    }
}

void Screen::blinkProcess() {
    digitalWrite(ledPin, !digitalRead(ledPin));

    ++blinkCounter;
    if (blinkCounter == 10) {
        blinkTicker.attach(0.1, [this]() {
            this->blinkProcess();
        });
    } else if (blinkCounter == 30) {
        blinkTicker.detach();
        digitalWrite(ledPin, LOW);
    }
}
