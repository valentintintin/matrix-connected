#ifndef MESSAGE_SETTING_H
#define MESSAGE_SETTING_H

#define MAX_LENGTH_MESSAGE 255

typedef struct MessageLongSettings {
    char message[MAX_LENGTH_MESSAGE];
    unsigned long durationSeconds;
} MessageLongSettings;

typedef struct MessageShortSettings {
    char message[8];
    unsigned long durationSeconds;
} MessageShortSettings;

#endif