#ifndef UTILS_H
#define UTILS_H

#include <WString.h>

//#define DEBUG

#ifdef DEBUG
#define DPRINT(...) Serial.print(__VA_ARGS__)
#define DPRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DPRINT(...)
#define DPRINTLN(...)
#endif

void millisToString(uint64_t milliseconds, String *timeString);

void utf8ToCp437(String &s);

#endif