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
    printf("  -h    with -l, print sizes like 1K 234M 2G etc.\n");
    printf("  -o    like -l, but do not list group information\n");
    printf("  -d    list directories themselves, not their contents\n");
    printf("  -f    generates an ls.txt   (!!not like original ls -f!!)\n");
    printf("  --help   display this help and exit\n");
}


// ls -ldho
void output_ldho(const char *dir) {
    printf("Creating ls.txt file in long format without group information and human-readable sizes for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_o(head);
    head = tag_h(head);
    head = tag_d(head);
    print_dynamic(head);
}

// ls -lhodf
void output_lhodf(const char *dir) {
    printf("Listing in long format without group information and human-readable sizes for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_o(head);
    head = tag_h(head);
    head = tag_d(head);
    print_dynamic_to_file(head);
}

// ls -dho
void output_dho(const char *dir) {
    printf("Listing in long format without group information and human-readable sizes for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_o(head);
    head = tag_h(head);
    head = tag_d(head);
    print_dynamic(head);
}


// ls -ldh
void output_ldh(const char *dir) {
    printf("Listing in long format and human-readable sizes for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_h(head);
    head = tag_d(head);
    print_dynamic(head);

}


// ls -oh
void output_oh(const char *dir) {
    printf("Listing in long format without group information for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_o(head);
    head = tag_h(head);
    print_dynamic(head);

}

// ls -lh
void output_lh(const char *dir) {
    printf("Listing in long format with human-readable sizes for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_h(head);
    print_dynamic(head);
}

// ls -dh
void output_dh(const char *dir) {
    printf("Listing in long format with human-readable sizes for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_h(head);
    print_normal(head);
}

// ls -ld
void output_ld(const char *dir) {
    printf("Listing in long format without group information for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_d(head);
    print_dynamic(head);
}

// ls -do
void output_do(const char *dir) {
    printf("Listing in long format without group information for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_d(head);
    head = tag_o(head);
    print_dynamic(head);
}

// ls -lo
void output_lo(const char *dir) {
    printf("Listing in long format without group information for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_o(head);
    print_dynamic(head);
}

// ls -l
void output_l(const char *dir) {
    printf("Listing in long format for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_dynamic(head);
}


// ls -d
void output_d(const char *dir) {
    printf("Listing directory only: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_d(head);
    print_normal(head);
}

// ls -h
void output_h (const char *dir) {
    printf("Listing with human-readable sizes for directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_normal(head);
}


// ls -o
void output_o (const char *dir) {
    printf("Listing in long format without group information: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_o(head);
    print_dynamic(head);
}

// ls -f
void output_f (const char *dir) {
    printf("Listing directory and create .txt file: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_normal_to_file(head);
}

// ls
void output_normal (const char *dir) {
    printf("Listing directory: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_ls_without_hidden_files(head);
}


// ls -lhof
void output_lhof(const char *dir) {
    printf("Listing in long format, human-readable, without group information and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_h(head);
    head = tag_o(head);
    print_dynamic_to_file(head);
}

// ls -ldhf
void output_ldhf(const char *dir) {
    printf("Listing in long format, directory only, human-readable and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_h(head);
    head = tag_d(head);
    print_dynamic_to_file(head);
}

// ls -ldof
void output_ldof(const char *dir) {
    printf("Listing in long format, directory only, without group information and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_d(head);
    head = tag_o(head);
    print_dynamic_to_file(head);
}

// ls -dhof
void output_dhof(const char *dir) {
    printf("Listing directory only, human-readable, without group information and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_d(head);
    head = tag_h(head);
    head = tag_o(head);
    print_normal_to_file(head);
}

// ls -lho
void output_lho(const char *dir) {
    printf("Listing in long format, human-readable and without group information: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_h(head);
    head = tag_o(head);
    print_dynamic(head);
}

// ls -ldf
void output_ldf(const char *dir) {
    printf("Listing in long format, directory only and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_d(head);
    print_dynamic_to_file(head);
}

// ls -lof
void output_lof(const char *dir) {
    printf("Listing in long format, without group information and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_o(head);
    print_dynamic_to_file(head);
}

// ls -dhf
void output_dhf(const char *dir) {
    printf("Listing directory only, human-readable and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_d(head);
    head = tag_h(head);
    print_normal_to_file(head);
}

// ls -dof
void output_dof(const char *dir) {
    printf("Listing directory only, without group information and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_d(head);
    head = tag_o(head);
    print_normal_to_file(head);
}

// ls -hof
void output_hof(const char *dir) {
    printf("Listing human-readable, without group information and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_h(head);
    head = tag_o(head);
    print_normal_to_file(head);
}

// ls -hf
void output_hf(const char *dir) {
    printf("Listing human-readable and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_h(head);
    print_normal_to_file(head);
}

// ls -of
void output_of(const char *dir) {
    printf("Listing without group information and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_o(head);
    print_normal_to_file(head);
}

// ls -df
void output_df(const char *dir) {
    printf("Listing directory only and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    head = tag_d(head);
    print_normal_to_file(head);
}

// ls -lf
void output_lf(const char *dir) {
    printf("Listing in long format and saving to file: %s\n", dir);
    insert_file_metadata(dir, 0);
    print_dynamic_to_file(head);
}


// wrong input
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
        if (action & ACTION_DIRECTORY_ONLY && action & ACTION_HUMAN_READABLE && action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_LONG_LIST && action & ACTION_OUTPUT_FILE) {
            output_lhodf(dir); // Falls -d, -h, -l, -f und -o gesetzt
        }
        else if (action & ACTION_DIRECTORY_ONLY && action & ACTION_HUMAN_READABLE && action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_LONG_LIST) {
            output_ldho(dir); // Falls -d, -h, -l und -o gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_DIRECTORY_ONLY && action & ACTION_HUMAN_READABLE && action & ACTION_OUTPUT_FILE) {
            output_ldhf(dir); // Falls -l, -d, -h und -f gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_HUMAN_READABLE && action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_OUTPUT_FILE) {
            output_lhof(dir); // Falls -l, -h, -o und -f gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_DIRECTORY_ONLY && action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_OUTPUT_FILE) {
            output_ldof(dir); // Falls -l, -d, -o und -f gesetzt
        }
        else if (action & ACTION_DIRECTORY_ONLY && action & ACTION_HUMAN_READABLE && action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_OUTPUT_FILE) {
            output_dhof(dir); // Falls -d, -h, -o und -f gesetzt
        }
        else if (action & ACTION_DIRECTORY_ONLY && action & ACTION_HUMAN_READABLE && action & ACTION_WITHOUT_GROUPINFORMATION) {
            output_dho(dir); // Falls -d, -h und -o gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_HUMAN_READABLE && action & ACTION_WITHOUT_GROUPINFORMATION) {
            output_lho(dir); // Falls -l, -h und -o gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_DIRECTORY_ONLY && action & ACTION_OUTPUT_FILE) {
            output_ldf(dir); // Falls -l, -d und -f gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_HUMAN_READABLE && action & ACTION_DIRECTORY_ONLY) {
            output_ldh(dir); // Falls -l, -h und -d gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_OUTPUT_FILE) {
            output_lof(dir); // Falls -l, -o und -f gesetzt
        }
        else if (action & ACTION_DIRECTORY_ONLY && action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_OUTPUT_FILE) {
            output_dof(dir); // Falls -d, -o und -f gesetzt
        }
        else if (action & ACTION_DIRECTORY_ONLY && action & ACTION_HUMAN_READABLE && action & ACTION_OUTPUT_FILE) {
            output_dhf(dir); // Falls -d, -h und -f gesetzt
        }
        else if (action & ACTION_HUMAN_READABLE && action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_OUTPUT_FILE) {
            output_hof(dir); // Falls -h, -o und -f gesetzt
        }
        else if (action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_HUMAN_READABLE) {
            output_oh(dir); // Falls -o und -h gesetzt
        }
        else if (action & ACTION_HUMAN_READABLE && action & ACTION_OUTPUT_FILE) {
            output_hf(dir); // Falls -h und -f gesetzt
        }
        else if (action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_DIRECTORY_ONLY) {
            output_do(dir); // Falls -o und -d gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_HUMAN_READABLE) {
            output_lh(dir); // Falls -l und -h gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_DIRECTORY_ONLY) {
            output_ld(dir); // Falls -l und -d gesetzt
        }
        else if (action & ACTION_DIRECTORY_ONLY && action & ACTION_HUMAN_READABLE) {
            output_dh(dir); // Falls -d und -h gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_OUTPUT_FILE) {
            output_lf(dir); // Falls -l und -f gesetzt
        }
        else if (action & ACTION_LONG_LIST && action & ACTION_WITHOUT_GROUPINFORMATION) {
            output_lo(dir); // Falls -l und -o gesetzt
        }
        else if (action & ACTION_WITHOUT_GROUPINFORMATION && action & ACTION_OUTPUT_FILE) {
            output_of(dir); // Falls -o und -f gesetzt
        }
        else if (action & ACTION_DIRECTORY_ONLY && action & ACTION_OUTPUT_FILE) {
            output_df(dir); // Falls -d und -f gesetzt
        }
        else if (action & ACTION_WITHOUT_GROUPINFORMATION) {
            output_o(dir); // Falls -o gesetzt
        }
        else if (action & ACTION_LONG_LIST) {
            output_l(dir); // Falls -l gesetzt
        }
        else if (action & ACTION_HUMAN_READABLE) {
            output_h(dir); // Falls -h gesetzt
        }
        else if (action & ACTION_DIRECTORY_ONLY) {
            output_d(dir); // Falls -d gesetzt
        }
        else if (action & ACTION_OUTPUT_FILE) {
            output_f(dir); // Falls -f gesetzt
        }
        else {
            output_normal(dir);// Standard Ausgabe
        }
    }

    return 0;
}