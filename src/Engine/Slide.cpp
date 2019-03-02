#include "Slide.h"

Slide::Slide(Screen *screen) : screen(screen), zone(PPmax72xxAnimate(&screen->matrix)), timer(Timer(TIME_DISPLAYED)) {
    widthX = screen->matrix.width();
}

bool Slide::show() {
    return zone.Animate(false);
}

void Slide::setZone(uint16_t startX, uint16_t widthX, textEffect_t textEffect) {
    this->startX = startX;
    this->widthX = widthX;
    this->textEffect = textEffect;

    if (startX == 0 && widthX == 0) {
        this->startX = 0;
        this->widthX = screen->matrix.width();
    }

    create();
}

void Slide::create() {
    zone.setText(getText(), textEffect, _TO_FULL, ANIMATION_SPEED, startX, widthX);
    timer.restart();
}

bool Slide::baseIsFinished() {
    return textEffect == _PRINT ? timer.hasExpired() : zone.AnimateDone();
}

void Slide::print() {
    Serial.print(getText());
    Serial.print(F("\t"));
    Serial.print(" IsFinished : ");
    Serial.print(isFinished());
    Serial.print(F("\t"));
    Serial.print(" Timer : ");
    Serial.print(timer.getTimeLeft());
    Serial.print(F("\t"));
    Serial.print(" ShouldRecreate : ");
    Serial.println(shouldRecreate());
}
