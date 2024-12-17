#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include <sys/stat.h>
#include "list.c"

#ifndef INSERT_H
#define INSERT_H

void insert(char *param_name, int param_type, int param_size,int param_rights,int param_UserID, int param_GroupID);
void printList();

#endif

void printAllDir(DIR *dir) {
    struct dirent *entry;


    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
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

        //param_type: 0 = Verzeichnis, nicht 0 = Datei
        insert(entry->d_name, param_type, fileStat.st_size, fileStat.st_mode & 0777, fileStat.st_uid, fileStat.st_gid);

        // Dateityp bestimmen
        printf("Metadaten für: %s\n", fullpath);
        printf("Dateityp: ");

        //else if (S_ISLNK(fileStat.st_mode)) printf("Symbolischer Link\n"); Erstmal nicht relevant für uns
        //else if (S_ISCHR(fileStat.st_mode)) printf("Zeichenorientiertes Gerät\n");
        //else if (S_ISBLK(fileStat.st_mode)) printf("Blockorientiertes Gerät\n");
        //else if (S_ISFIFO(fileStat.st_mode)) printf("FIFO/Named Pipe\n");
        //else if (S_ISSOCK(fileStat.st_mode)) printf("Socket\n");


        // Zeitstempel (Änderung, Zugriff, Erstellung)
        printf("Letzter Zugriff: %s", ctime(&fileStat.st_atime));
        printf("Letzte Änderung: %s", ctime(&fileStat.st_mtime));
        printf("Letzte Status-Änderung: %s", ctime(&fileStat.st_ctime));


    }
}


void main01() {
    const char *str = "/home/art";
    print_file_metadata(str);
    printList();
}
