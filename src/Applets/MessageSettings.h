#ifndef MESSAGE_SETTING_H
#define MESSAGE_SETTING_H

typedef struct MessageLongSettings {
    char message[126];
    uint64_t durationSeconds;
} MessageLongSettings;

typedef struct MessageShortSettings {
    char message[8];
    uint64_t durationSeconds;
} MessageShortSettings;

#endif