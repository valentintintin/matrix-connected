#ifndef UTILS_H
#define UTILS_H

#define AP_SSID "Horloge Willyam"

#include <Arduino.h>

//#define DEBUG

#ifdef DEBUG
#define DPRINT(...) Serial.print(__VA_ARGS__)
#define DPRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DPRINT(...)
#define DPRINTLN(...)
#endif

void millisToString(uint64_t milliseconds, String *timeString);
void millisToString(uint64_t milliseconds, char *timeString);

uint8_t utf8Ascii(uint8_t ascii);
void utf8Ascii(char* s);
String utf8ascii(String &s);
void utf8AsciiS(String &s);

#endif