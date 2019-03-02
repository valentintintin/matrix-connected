#include "Screen.h"
#include "Slide.h"

Screen::Screen(byte csPin, byte hDisplays) : matrix(PPMax72xxPanel(csPin, hDisplays, 1)) {
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
    slides.push(slide);
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
    }

    return shouldRefresh;
}

void Screen::setMainSlide(Slide *slide) {
    mainSlide = slide;
}

const Slide *Screen::getMainSlide() {
    return mainSlide;
}

void Screen::setState(bool on) {
    matrix.setIntensity(0);
    matrix.fillScreen(LOW);
    matrix.write();
    enabled = on;
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
