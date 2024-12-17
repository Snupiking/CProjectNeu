#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


void process_input(int argc, char *argv[]) {
    int long_format = 0;
    int human_readable = 0;
    char *dir = getenv("HOME");  // HOME als Standard


    if (dir == NULL) {
        dir = ".";  // Für den Fall das HOME nicht geöffnet werden kann, wird das aktuelle Verzeichnis verwendet
    }


    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: ls [OPTION] [DIR]\n");
            printf("List information about the files in DIR.\n");
            printf("\nOptions:\n");
            printf("  -l    use a long listing format\n");
            printf("  -h    print human-readable file sizes\n");
            printf("  --help   display this help and exit\n");
            return;
        } else if (argv[i][0] == '-') {
            for (int j = 1; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'l') {
                    long_format = 1;  // -l
                } else if (argv[i][j] == 'h') {
                    human_readable = 1;  // -h
                } else {
                    // Ungültige eingabe
                    printf("Invalid option: -%c\n", argv[i][j]);
                    printf("Use '--help' for usage instructions.\n");
                    return;
                }
            }
        } else {
            // Falls ein Verzeichnis angegeben wurde, wird es als neues Verzeichnis verwendet
            dir = argv[i];
        }
    }

    // Überprüfen, ob das angegebene Verzeichnis existiert
    DIR *d = opendir(dir);
    if (d == NULL) {
        // Fehlerfall:
        perror("Invalid directory");
        return;
    }
    closedir(d);

    // Ausgabe -lh
    if (long_format && human_readable) {
        printf("Listing in long format with human-readable sizes for directory: %s\n", dir);

    }
    // Ausgabe -l
    else if (long_format) {
        printf("Listing in long format for directory: %s\n", dir);

    }
    // Ausgabe -h
    else if (human_readable) {
        printf("Listing with human-readable sizes for directory: %s\n", dir);

    }

    //Standardausgabe
    else {
        printf("Listing directory: %s\n", dir);

    }
}

int main(int argc, char *argv[]) {
    process_input(argc, argv);
    return 0;
}