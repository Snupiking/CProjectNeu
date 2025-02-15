#ifndef LIST_H
#define LIST_H

#include <dirent.h>
#include <stddef.h>
#include <sys/types.h>

// Strukturdefinition des Elements
typedef struct element {
    char *name;  // Name der Datei/des Verzeichnisses
    int type;    // Typ: 0=Datei, 1=Verzeichnis
    int size;    // Größe der Datei oder des Verzeichnisses
    char size_unit;// einheit der groeße z.b. b,k,g,t 
    int rights;  // Rechte
    int UserID;  // Benutzer-ID
    int groupID; // Gruppen-ID
    char *lastUse;           // Letzter Zugriff
    char *lastChange;        // Letzte Änderung
    char *lastStatusChange;
    int count_hardlinks;// Letzter Statuswechsel
    char *temp_sizes;
    char *param_path;
    struct element *next;    // Zeiger auf das nächste Element
} Element;

// Funktionen für die Liste
extern Element *head;

void insert(char *param_name, int param_type, int param_size, int param_rights,
            int param_UserID, int param_GroupID, char *param_lastUse,
            char *param_lastChange, char *param_lastStatusChange, int count_hardlinks, char *param_path, char *temp_sizes);

char *delete(void);
void printList(void);
void print_l();
void print_ls_without_hidden_files();
void ls_r(const char *current_path);
void format_rights(int rights, char *output);

#endif // LIST_H
