#ifndef UTILS_H
#define UTILS_H

#define VERSION 1.14
#define AP_SSID "Horloge"

#ifdef VALENTIN
#define AP_SSID "PixelClock"
#elif defined(WILLYAM)
#define AP_SSID "Horloge Willyam"
#elif defined(VALENTIN_SMALL)
#define AP_SSID "PixelClock Salle de Bain"
#elif defined(VALENTIN_SMALL_STATE)
#define AP_SSID "PixelClock HomeAssistant"
#endif

#include <Arduino.h>

#ifdef DEBUG
#define DPRINT(...) Serial.print(__VA_ARGS__)
#define DPRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DPRINT(...)
#define DPRINTLN(...)
#endif

void millisToString(unsigned long milliseconds, char *timeString, bool withThirdData = true);

byte utf8Ascii(byte ascii);
void utf8Ascii(char* s);

#endif