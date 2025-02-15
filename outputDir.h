#ifndef OUTPUTDIR_H
#define OUTPUTDIR_H

#include "list.h"
#include <dirent.h>  // Für DIR und struct dirent

// Funktion zur Ausgabe aller Dateien in einem Verzeichnis
void printAllDir(const char *dirpath);

// Funktion, um Metadaten von Dateien und Verzeichnissen auszugeben
void print_file_metadata(const char *dirpath);

// Prototypen für Funktionen aus list.c
void insert(char *param_name, int param_type, int param_size, int param_rights,
            int param_UserID, int param_GroupID, char *param_lastUse,
            char *param_lastChange, char *param_lastStatusChange, int count_hardlinks, char *param_path,char *temp_sizes);
void printList();
void insert_file_metadata(const char *dirpath, int recursive_if_1);
void print_dynamic(Element *head);
void print_normal(Element *head);
void print_dynamic_to_file(Element *head);
void print_normal_to_file(Element *head);
void print_ls_without_hidden_files(Element *head);
#endif
