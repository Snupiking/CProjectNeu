#include <stdio.h>
#include <dirent.h>
#include <string.h>

DIR *openDir(char *path) {
    // Reads and outputs the contents of the given directory
    DIR *dir;
    struct dirent *entry;

    if (path == NULL) {
        fprintf(stderr, "No path has been given.\n");
    }

    dir = opendir(path); // Open the given directory
    if (dir == NULL) {
        perror("opendir");
    }
    return dir;
}

void printDir(DIR *dir) {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }
        if (entry->d_type == DT_DIR) {
            printf("/");
        }
        printf("%s\n", entry->d_name);
    }
}

void printAllDir(DIR *dir) {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
}

void main01() {
    const char *str = "/home/art";
    printDir(opendir(str));
}
