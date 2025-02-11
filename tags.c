#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "list.h"
#include "tags.h"



Element *tag_h(Element *head) {
    Element *current = head;

    const char *sizes[] = {"B", "K", "M", "G", "T"};

    while (current != NULL) {
        int i = 0;
        double dbl_size = (double)current->size;

        // Umwandlung in human-readable Formate
        while (dbl_size >= 1024 && i < 4) {
            dbl_size /= 1024;
            i++;
        }

        current->size_unit = sizes[i][0]; // Einheit speichern

        char size_str[20]; // Speicher für String mit Größe und Einheit

        // Erstelle die Darstellung (z. B. "1.5K" oder "512B")
        if (dbl_size < 10) {
            snprintf(size_str, sizeof(size_str), "%.1f%c", dbl_size, current->size_unit);
        } else {
            snprintf(size_str, sizeof(size_str), "%.0f%c", dbl_size, current->size_unit);
        }

        // Speicher für `temp_sizes` anpassen
        current->temp_sizes = realloc(current->temp_sizes, strlen(size_str) + 1);
        if (current->temp_sizes == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }

        strcpy(current->temp_sizes, size_str);
        current = current->next;
    }

    return head; // Veränderte Liste zurückgeben
}

Element *tag_o(Element *head) {
    Element *current = head;

    while (current != NULL) {
        current->groupID = -1;  // Setze GroupID auf NULL, falls GroupID ein Pointer ist
        current = current->next;
    }

    return head;  // Gib die modifizierte Liste zurück
}


Element *tag_d(Element *head) {
    Element *current = head;
    Element *prev = NULL;

    while (current != NULL) {
        if (current->type != 1) { // Kein Verzeichnis
            Element *to_delete = current;
            if (prev == NULL) { // Kopf der Liste
                head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(to_delete); // Speicher freigeben
        } else {
            prev = current;
            current = current->next;
        }
    }

    return head;
}


// Annahme: Element ist deine Listenelementstruktur
void ls_r(const char *current_path) {
    Element *curr = head;

    // 1. Ausgabe des aktuellen Verzeichnisses
    printf("\n%s:\n", current_path);

    // 2. Dateien und Verzeichnisse im aktuellen Verzeichnis ausgeben
    while (curr != NULL) {
        // Prüfen, ob das Element im aktuellen Verzeichnis liegt
        if (strcmp(curr->param_path, current_path) == 0) {
            if (curr->type == 0) { // Reguläre Datei
                printf("%s\n", curr->name);
            } else if (curr->type == 1) { // Verzeichnis
                printf("%s/\n", curr->name);
            }
        }
        curr = curr->next;
    }

    // 3. Rekursiv in Unterverzeichnisse gehen
    curr = head;
    while (curr != NULL) {
        if (curr->type == 1 && strcmp(curr->param_path, current_path) == 0) {
            // Rekursiver Aufruf für Unterverzeichnisse
            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", current_path, curr->name);
            ls_r(new_path);
        }
        curr = curr->next;
    }
}


