#include<list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "list.h"
#include "tags.h"

static Element *head = NULL;


//TODO
// h wird bei ls ignoriert ohne l oder s
void print_h()
{
    Element *current = head;

    const char *sizes[] = {"B", "K", "M", "G", "T"};

    // für alle elemente
    while (current != NULL)
    {
        int i = 0;
        double dbl_size = (double)current->size;
        // für ein element
        //i < 4 könnte bei größeren files unnötig werden idk though
        while (dbl_size >= 1024 && i < 4)
        {

            dbl_size /= 1024;

            current->size = (int)dbl_size;
            i++;
        }

        current->size_unit = sizes[i][0];

        char size_str[20]; // adjust the size as needed

        size_t total_length = strlen(size_str) + 2; // +1 für Einheit, +1 für Nullterminator
        current->temp_sizes = malloc(total_length);

        if (current->temp_sizes == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        if (dbl_size < 10)
        {
            snprintf(size_str, sizeof(size_str), "%0.1f%c", dbl_size, current->size_unit);
            
        }
        else
        {
            snprintf(size_str, sizeof(size_str), "%.0d%c", current->size, current->size_unit);
        }

        
        strcpy(current->temp_sizes, size_str);
        
        current = current->next;
        
    }
}
//TODO
void print_o()
{
    Element *current = head;
    char rights[10];
    
    // Header
    printf("Permissions   Links UID  Size     Last Change              Name\n");
    printf("----------------------------------------------------------------------------------------\n");
    int sum_size = 0; // in kilo
    
    while(current != NULL){
        sum_size+=current->size;
        current = current->next;
    }
    current = head;
    sum_size = round(sum_size/1000);
    printf("total %d\n",sum_size);
    while (current != NULL) {
        
        if(current->temp_sizes == NULL){
            current->temp_sizes = malloc(40);
            sprintf(current->temp_sizes,"%d",current->size);
        }
        // Rechte in richtiges Format formatieren
        format_rights(current->rights, rights);
        
        // Printed jede value die benötigt wird
        printf("%s    %3d    %4d %s %s %s \n",
               rights,                   // Permissions
               current->count_hardlinks, // Hardlink Anzahl
               current->UserID,          // User ID
               current->temp_sizes,      // Größe der Datei
               current->lastChange,      // Zeit der letzten veränderung
               current->name             // Name der Datei oder des Verzeichnisses
        );

        current = current->next;
    }
}

void print_d()
{
    Element *current = head;

    // Header
    printf("Directories:\n");
    printf("----------------------------------------------------------------------------------------\n");

    while (current != NULL)
    {
        // Prüfen, ob das aktuelle Element ein Verzeichnis ist
        if (current->type == 1)
        {
            printf("%s\n", current->name); // Nur den Namen des Verzeichnisses ausgeben
        }

        current = current->next;
    }
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


