#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "outputDir.h"
#include "list.h"
#include "tags.h"

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
    print_l();

}

void output_long_listing(const char *dir) {
    printf("Listing in long format for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_l();
}

void output_dho(const char *dir) {
    printf("Listing in long format without group information and human-readable sizes for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_d();
    print_o();
    print_h();
}

void output_ldh(const char *dir) {
    printf("Listing in long format and human-readable sizes for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_d();
    print_l();
    print_h();
}

void output_human_readable(const char *dir) {
    printf("Listing with human-readable sizes for directory: %s\n", dir);
    printAllDir(dir);
    print_h();
}

void output_long_human_readable(const char *dir) {
    printf("Listing in long format with human-readable sizes for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_l();
    print_h();
}

void output_directory_only(const char *dir) {
    printf("Listing directory only: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_d();

}

void output_without_groupinformation() {
    printf("Listing in long format without group information: \n");
    insert_file_metadata(".", 0);
    print_o();
}

void output_without_groupinformation_and_human_readable(const char *dir) {
    printf("Listing in long format without group information for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_o();
    print_h();
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
        if (action & ACTION_DIRECTORY_ONLY && action & ACTION_HUMAN_READABLE && action & ACTION_WITHOUT_GROUPINFORMATION) {
            output_dho(dir); // Falls -d, -h und -o gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_HUMAN_READABLE && action & ACTION_DIRECTORY_ONLY) {
            output_ldh(dir); // Falls -l, -h und -d gesetzt
        }
        else if (action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_HUMAN_READABLE) {
            output_without_groupinformation_and_human_readable(dir); // Falls -o und -h gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_HUMAN_READABLE) {
            output_long_human_readable(dir); // Falls -l und -h gesetzt
        }
        else if (action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_HUMAN_READABLE) {
            output_without_groupinformation(dir); // Falls -o und -h gesetzt
        }
        else if (action & ACTION_WITHOUT_GROUPINFORMATION) {
            output_without_groupinformation(dir); // Falls -o gesetzt
        }
        else if (action & ACTION_LONG_LIST) {
            output_long_listing(dir); // Falls -l gesetzt
        }
        else if (action & ACTION_HUMAN_READABLE) {
            output_human_readable(dir); // Falls -h gesetzt
        }
        else if (action & ACTION_DIRECTORY_ONLY) {
            output_directory_only(dir); // Falls -d gesetzt
        }
        else {
            output_listing(dir); // Standard Ausgabe
        }
    }


    return 0;
}