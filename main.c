#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "outputDir.h"
#include "list.h"

// Output-Funktionen
void output_help() {
    printf("Usage: ls [OPTION] [DIR]\n");
    printf("List information about the files in DIR.\n");
    printf("\nOptions:\n");
    printf("  -l    use a long listing format\n");
    printf("  -h    print human-readable file sizes\n");
    printf("  --help   display this help and exit\n");
}

void output_listing(const char *dir) {
    printf("Listing directory: %s\n", dir);
    insert_file_metadata(dir);
    print_l();

}

void output_long_listing(const char *dir) {
    printf("Listing in long format for directory: %s\n", dir);
    // TODO: Hier die Logik für das lange Auflisten der Dateien einfügen
}

void output_human_readable(const char *dir) {
    printf("Listing with human-readable sizes for directory: %s\n", dir);
    // TODO: Hier die Logik für die Ausgabe mit menschenlesbaren Größen einfügen
}

void output_long_human_readable(const char *dir) {
    printf("Listing in long format with human-readable sizes for directory: %s\n", dir);
    // TODO: Hier die Logik für die kombinierte Ausgabe einfügen
}

void output_invalid_option() {
    printf("Invalid option provided. Use '--help' for usage instructions.\n");
}

int main(int argc, char *argv[]) {
    char *dir = NULL;
    ActionType action = process_input(argc, argv, &dir);  // Eingabeverarbeitung aufrufen

    // Überprüfen der kombinierten Optionen
    if (action & ACTION_HELP) {
        output_help();
    } else {
        if (action & ACTION_LONG_LIST) {
            output_long_listing(dir); // Falls -l gesetzt
        }
        if (action & ACTION_HUMAN_READABLE) { // Sollte gelöscht werden, da es nichts verändert am standardoutput
            output_human_readable(dir); // Falls -h gesetzt
        }
        if (!(action & ACTION_LONG_LIST) && !(action & ACTION_HUMAN_READABLE)) {
            output_listing(dir); // Standard Ausgabe
        }
    }


    return 0;
}
