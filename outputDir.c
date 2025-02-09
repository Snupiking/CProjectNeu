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

void insert_file_metadata(const char *dirpath, int recursive_if_1) {
    struct dirent *entry;
    DIR *dir = opendir(dirpath);
    if (dir == NULL) {
        perror("Fehler beim Öffnen des Verzeichnisses");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char fullpath[1024];
        char partial_path[1024];

        // "." und ".." ignorieren
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Pfad zusammenbauen: dirpath + "/" + entry->d_name
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);
        snprintf(partial_path, sizeof(partial_path), "%s/", dirpath);


        struct stat fileStat;

        // Metadaten der Datei oder des Verzeichnisses lesen
        if (stat(fullpath, &fileStat) < 0) {
            perror("Fehler beim Lesen der Metadaten");
            continue;
        }

        int param_type;
        if (S_ISREG(fileStat.st_mode)) param_type = 0;
        else if (S_ISDIR(fileStat.st_mode)) param_type = 1;

        else {
            perror("Weder Verzeichnis noch Datei übergeben");
            continue;

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

            free(param_lastUse);
            exit(EXIT_FAILURE);
        }
        strcpy(param_lastChange, ctime(&fileStat.st_mtime));
        param_lastChange[strlen(param_lastChange) - 1] = '\0'; // Entfernt das \n von param_lastChange

        // Speichert die veränderung des status
        char *param_lastStatusChange = malloc(strlen(ctime(&fileStat.st_ctime)) + 1);
        if (param_lastStatusChange == NULL) {
            perror("Memory allocation failed for param_lastStatusChange");
            free(param_lastUse);
            free(param_lastChange);
            exit(EXIT_FAILURE);
        }
        strcpy(param_lastStatusChange, ctime(&fileStat.st_ctime));

        // Speichert die Anzahl an hardlinks
        int *count_hardlinks = malloc(sizeof(int));
        if (count_hardlinks == NULL) {
            perror("Memory allocation failed for count_hardlinks");
            free(param_lastUse);
            free(param_lastChange);
            free(param_lastStatusChange);
            exit(EXIT_FAILURE);
        }
        *count_hardlinks = (int)(fileStat.st_nlink);

        insert(entry->d_name, param_type, fileStat.st_size, fileStat.st_mode & 0777, fileStat.st_uid, fileStat.st_gid
            , param_lastUse, param_lastChange, param_lastStatusChange, *count_hardlinks, partial_path, NULL);

        // Rekursiver Aufruf für Verzeichnisse
        if (param_type == 1 && recursive_if_1 == 1) {
            insert_file_metadata(fullpath, recursive_if_1);
        }

        // Speicher freigeben
        free(param_lastUse);
        free(param_lastChange);
        free(param_lastStatusChange);
        free(count_hardlinks);
    }

    closedir(dir);
}

void print_dynamic(Element *head) {
    int include_groupID = 0;
    int include_UserID = 0;
    int include_size = 0;
    int include_rights = 0;
    int include_links = 0;
    int include_lastChange = 0;

    char rights[10];

    Element *current = head;
    // Prüfe, ob die Spalten benötigt werden
    while (current != NULL) {
        if (current->groupID != -1) include_groupID = 1;
        if (current->UserID != -1) include_UserID = 1;
        if (current->size != -1) include_size = 1;
        if (current->rights != -1) include_rights = 1;
        if (current->count_hardlinks != -1) include_links = 1;
        if (current->lastChange != NULL) include_lastChange = 1;
        current = current->next;
    }

    // Header dynamisch erzeugen
    printf("%-15s", "Permissions");
    if (include_links) printf("%-6s", "Links");
    if (include_UserID) printf("%-6s", "UID");
    if (include_groupID) printf("%-6s", "GID");
    if (include_size) printf("%-12s", "Size");
    if (include_lastChange) printf("%-25s", "Last Change");
    printf("Name\n");
    printf("----------------------------------------------------------------------------------------\n");

    // Ausgabe der Werte
    current = head;
    while (current != NULL) {
        // Dynamische Zuweisung der Größe
        if (current->temp_sizes == NULL) {
            current->temp_sizes = malloc(40);  // Puffergröße sicherstellen
            if (current->temp_sizes == NULL) {
                perror("Memory allocation failed for temp_sizes");
                exit(EXIT_FAILURE);
            }
            sprintf(current->temp_sizes, "%d", current->size);  // Setze die Größe als Text
        }

        // Berechtigungen formatieren
        format_rights(current->rights, rights);

        // Dynamische Ausgabe
        printf("%-15s", rights);                    // Permissions
        if (include_links) printf("%-6d", current->count_hardlinks);  // Hardlink Anzahl
        if (include_UserID) printf("%-6d", current->UserID);           // User ID
        if (include_groupID) printf("%-6d", current->groupID);          // Group ID
        if (include_size) printf("%-8s", current->temp_sizes);         // Größe der Datei
        if (include_lastChange) printf("%-28s", current->lastChange);   // Zeit der letzten Veränderung
        printf("%-40s\n", current->name);           // Name der Datei oder des Verzeichnisses
        current = current->next;
    }
}

void print_normal(Element *head) {

    Element *current = head;

    // Ausgabe der Werte
    current = head;
    while (current != NULL) {

        printf("%s\n", current->name);           // Name der Datei oder des Verzeichnisses


        current = current->next;
    }
}

void print_dynamic_to_file(Element *head) {
    FILE *file = fopen("ls.txt", "w");  // Datei ls.txt öffnen oder erstellen
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);  // Falls die Datei nicht geöffnet werden kann, Fehler ausgeben
    }

    int include_groupID = 0;
    int include_UserID = 0;
    int include_size = 0;
    int include_rights = 0;
    int include_links = 0;
    int include_lastChange = 0;

    char rights[10];

    Element *current = head;

    // Prüfe, ob die Spalten benötigt werden
    while (current != NULL) {
        if (current->groupID != -1) include_groupID = 1;
        if (current->UserID != -1) include_UserID = 1;
        if (current->size != -1) include_size = 1;
        if (current->rights != -1) include_rights = 1;
        if (current->count_hardlinks != -1) include_links = 1;
        if (current->lastChange != NULL) include_lastChange = 1;
        current = current->next;
    }

    // Header dynamisch erzeugen und in Datei schreiben
    fprintf(file, "%-15s", "Permissions");
    if (include_links) fprintf(file, "%-6s", "Links");
    if (include_UserID) fprintf(file, "%-6s", "UID");
    if (include_groupID) fprintf(file, "%-6s", "GID");
    if (include_size) fprintf(file, "%-12s", "Size");
    if (include_lastChange) fprintf(file, "%-25s", "Last Change");
    fprintf(file, "Name\n");
    fprintf(file, "----------------------------------------------------------------------------------------\n");

    // Ausgabe der Werte in die Datei
    current = head;
    while (current != NULL) {

        // Dynamische Zuweisung der Größe
        if (current->temp_sizes == NULL) {
            current->temp_sizes = malloc(40);  // Puffergröße sicherstellen
            sprintf(current->temp_sizes, "%d", current->size);  // Setze die Größe als Text
        }

        // Berechtigungen formatieren
        format_rights(current->rights, rights);

        // Dynamische Ausgabe in die Datei
        fprintf(file, "%-15s", rights);                    // Permissions
        if (include_links) fprintf(file, "%-6d", current->count_hardlinks);  // Hardlink Anzahl
        if (include_UserID) fprintf(file, "%-6d", current->UserID);           // User ID
        if (include_groupID) fprintf(file, "%-6d", current->groupID);          // Group ID
        if (include_size) fprintf(file, "%-8s", current->temp_sizes);         // Größe der Datei
        if (include_lastChange) fprintf(file, "%-28s", current->lastChange);   // Zeit der letzten Veränderung
        fprintf(file, "%-40s\n", current->name);           // Name der Datei oder des Verzeichnisses

        current = current->next;
    }

    fclose(file);  // Datei schließen
}

void print_normal_to_file(Element *head) {


    FILE *file = fopen("ls.txt", "w");  // Datei ls.txt öffnen oder erstellen
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);  // Falls die Datei nicht geöffnet werden kann, Fehler ausgeben
    }

    Element *current = head;

    // Ausgabe der Werte
    current = head;
    while (current != NULL) {

        fprintf(file, "%s\n", current->name);           // Name der Datei oder des Verzeichnisses


        current = current->next;
    }
    fclose(file);  // Datei schließen
}

void print_ls_without_hidden_files(Element *head)
{
    Element *current = head;
    while (current != NULL) {
        //Filtert alle Dateien, die mit "." anfangen oder nicht existieren
        if (current->name != NULL && current->name[0] == '.') {
            current = current->next;
            continue;
        }

        printf("%s \n", current->name);
        current = current->next;
    }
}


