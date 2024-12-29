#include "outputDir.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "list.h"





void printAllDir(const char *dirpath) {
    struct dirent *entry;
    DIR *dir = opendir(dirpath);


    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

    void print_file_metadata(const char *dirpath) {
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
        else{ perror("Weder Verzeichnis noch Datei übergeben");break;}
        char *param_lastUse = ctime(&fileStat.st_atime);
        char *param_lastChange = ctime(&fileStat.st_mtime);
        char *param_lastStatusChange = ctime(&fileStat.st_ctime);

        //param_type: 0 = Verzeichnis, nicht 0 = Datei
        insert(entry->d_name, param_type, fileStat.st_size, fileStat.st_mode & 0777, fileStat.st_uid, fileStat.st_gid
            , param_lastUse,param_lastChange,param_lastStatusChange);

        // Dateityp bestimmen
        printf("Metadaten für: %s\n", fullpath);
        printf("Dateityp: ");

    }
}


void main01() {
    const char *str = "/home/art";
    print_file_metadata(str);
    printList();
}
