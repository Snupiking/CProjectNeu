#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "list.h"
#include "outputDir.h"


void printAllDir(const char *dirpath) {
    struct dirent *entry;
    DIR *dir = opendir(dirpath);


    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

void insert_file_metadata(const char *dirpath) {
    struct dirent *entry;
    DIR *dir = opendir(dirpath);
    while ((entry = readdir(dir)) != NULL) {
        char fullpath[1024];

        // "." und ".." ignorieren
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Pfad zusammenbauen: dirpath + "/" + entry->d_name
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);


        struct stat fileStat;

        // Metadaten der Datei oder des Verzeichnisses lesen
        if (stat(fullpath, &fileStat) < 0) {
            perror("Fehler beim Lesen der Metadaten");
            return;
        }

        int param_type;
        if (S_ISREG(fileStat.st_mode)) param_type = 0;
        else if (S_ISDIR(fileStat.st_mode)) param_type = 1;
        else {
            perror("Weder Verzeichnis noch Datei übergeben");
            break;
        }

        //Speicher die Zeit ab, wann es letztes mal verwendet wurde
        char *param_lastUse = malloc(strlen(ctime(&fileStat.st_atime)) + 1);
        if (param_lastUse == NULL) {
            perror("Memory allocation failed for param_lastUse");
            exit(EXIT_FAILURE);
        }
        strcpy(param_lastUse, ctime(&fileStat.st_atime));

        // Speichert die Zeit hab wann es letztes mal verändert wurde
        char *param_lastChange = malloc(strlen(ctime(&fileStat.st_mtime)) + 1);
        if (param_lastChange == NULL) {
            perror("Memory allocation failed for param_lastChange");
            exit(EXIT_FAILURE);
        }
        strcpy(param_lastChange, ctime(&fileStat.st_mtime));
        param_lastChange[strlen(param_lastChange) - 1] = '\0'; // Entfernt das \n von param_lastChange

        // Speichert die veränderung des status
        char *param_lastStatusChange = malloc(strlen(ctime(&fileStat.st_ctime)) + 1);
        if (param_lastStatusChange == NULL) {
            perror("Memory allocation failed for param_lastStatusChange");
            exit(EXIT_FAILURE);
        }
        strcpy(param_lastStatusChange, ctime(&fileStat.st_ctime));

        // Speichert die Anzahl an hardlinks
        int *count_hardlinks = malloc(sizeof(int));
        if (count_hardlinks == NULL) {
            perror("Memory allocation failed for count_hardlinks");
            exit(EXIT_FAILURE);
        }
        *count_hardlinks = (int)(fileStat.st_nlink);

        insert(entry->d_name, param_type, fileStat.st_size, fileStat.st_mode & 0777, fileStat.st_uid, fileStat.st_gid
            , param_lastUse,param_lastChange,param_lastStatusChange, *count_hardlinks);

    }
}


