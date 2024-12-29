#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

// ActionType Enum mit Bitmasken für verschiedene Optionen
typedef enum {
    ACTION_LIST = 1,           // 0b0001 - Standard "ls"
    ACTION_LONG_LIST = 2,      // 0b0010 - "ls -l"
    ACTION_HUMAN_READABLE = 4, // 0b0100 - "ls -h"
    ACTION_HELP = 8            // 0b1000 - "--help"
} ActionType;

// Funktionsprototypen
ActionType process_input(int argc, char *argv[], char **dir);

#endif
