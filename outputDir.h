#ifndef OUTPUTDIR_H
#define OUTPUTDIR_H

#include <dirent.h>  // Für DIR und struct dirent

// Funktion zur Ausgabe aller Dateien in einem Verzeichnis
void printAllDir(const char *dirpath);

// Funktion, um Metadaten von Dateien und Verzeichnissen auszugeben
void print_file_metadata(const char *dirpath);

// Prototypen für Funktionen aus list.c
void insert(char *param_name, int param_type, int param_size, int param_rights,
            int param_UserID, int param_GroupID, char *param_lastUse,
            char *param_lastChange, char *param_lastStatusChange, int count_hardlinks);
void printList();

#endif
