#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

ActionType process_input(int argc, char *argv[], char **dir) {
    int long_format = 0;
    int human_readable = 0;
    *dir = getenv("HOME");  // Standardmäßig das Home-Verzeichnis

    if (*dir == NULL) {
        *dir = ".";  // Wenn HOME nicht existiert, benutze das aktuelle Verzeichnis
    }

    ActionType action = ACTION_LIST;  // Standardmäßig wird die Liste angezeigt

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            return ACTION_HELP;
        } else if (argv[i][0] == '-') {
            for (int j = 1; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'l') {
                    action |= ACTION_LONG_LIST;  // Kombiniere mit long format
                } else if (argv[i][j] == 'h') {
                    action |= ACTION_HUMAN_READABLE; // Kombiniere mit human readable
                } else if (argv[i][j] == 'd') {
                    action |= ACTION_DIRECTORY_ONLY;  // Kombiniere mit Verzeichnis-Option
                } else if (argv[i][j] == 'o') {
                    action |= ACTION_WITHOUT_GROUPINFORMATION;  // Kombiniere mit -o
                } else {
                    printf("Invalid option: -%c\n", argv[i][j]);
                    printf("Use '--help' for usage instructions.\n");
                    exit(EXIT_FAILURE);  // Programm mit Fehler beenden
                }
            }
        } else {
            *dir = argv[i];  // Verzeichnis setzen
        }
    }

    DIR *d = opendir(*dir);
    if (d == NULL) {
        perror("Invalid directory");
        exit(EXIT_FAILURE);  // Programm mit Fehler beenden
    }
    closedir(d);

    return action;  // Gib die kombinierten Optionen zurück
}
