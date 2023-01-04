#ifndef UTILS_H
#define UTILS_H

#define AP_SSID "Horloge"

#ifdef VALENTIN
#define AP_SSID "PixelClock"
#elif defined(WILLYAM)
#define AP_SSID "Horloge Willyam"
#elif defined(VALENTIN_SMALL)
#define AP_SSID "PixelClock Salle de Bain"
#endif

#include <Arduino.h>

#ifdef DEBUG
#define DPRINT(...) Serial.print(__VA_ARGS__)
#define DPRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DPRINT(...)
#define DPRINTLN(...)
#endif

void millisToString(uint64_t milliseconds, char *timeString, bool withThirdData = true);

uint8_t utf8Ascii(uint8_t ascii);
void utf8Ascii(char* s);

#endif