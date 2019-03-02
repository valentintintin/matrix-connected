#ifndef UTILS_H
#define UTILS_H

#include <WString.h>

void millisToString(uint64_t milliseconds, String *timeString);

void utf8ToCp437(String &s);

#endif