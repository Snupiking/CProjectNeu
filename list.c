#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "list.h"


static Element *head = NULL;



void insert(char *param_name, int param_type, int param_size, int param_rights,
            int param_UserID, int param_GroupID, char *param_lastUse,
            char *param_lastChange, char *param_lastStatusChange, int count_hardlinks)
{

    Element *newElement = (Element *)malloc(sizeof(Element));
    Element *curr = head;
    // Fall 1: head
    if (head == NULL)
    {
        head = newElement;
        newElement->next = NULL;
    }
    // Fall 2:tail
    else
    {
        while (curr->next != NULL)
        {
            curr = curr->next;
            // printf("%d ",curr->value);
        }
        curr->next = newElement;
    }
    newElement->name = param_name;
    newElement->type = param_type;
    newElement->size = param_size;
    newElement->rights = param_rights;
    newElement->UserID = param_UserID;
    newElement->groupID = param_GroupID;
    newElement->lastUse = param_lastUse;
    newElement->lastChange = param_lastChange;
    newElement->lastStatusChange = param_lastStatusChange;
    newElement->count_hardlinks = count_hardlinks;

    newElement->next = NULL;
}

char *delete(void)
{
    Element *temp = head->next;
    char *temp_name = head->name;
    free(head);
    head = temp;
    return temp_name;
}

void printList()
{
    while (head != NULL)
    {
        printf("%s\n", head->name);
        head = head->next;
    }
}
//
void format_rights(int rights, char *output) {
    output[0] = (rights & 0400) ? 'r' : '-';
    output[1] = (rights & 0200) ? 'w' : '-';
    output[2] = (rights & 0100) ? 'x' : '-';
    output[3] = (rights & 0040) ? 'r' : '-';
    output[4] = (rights & 0020) ? 'w' : '-';
    output[5] = (rights & 0010) ? 'x' : '-';
    output[6] = (rights & 0004) ? 'r' : '-';
    output[7] = (rights & 0002) ? 'w' : '-';
    output[8] = (rights & 0001) ? 'x' : '-';
    output[9] = '\0';
}

// Hauptfunktion zum Ausdrucken der Linked List im Stil von `ls -l`
void print_l()
{
    Element *current = head;
    char rights[10];

    // Header
    printf("Permissions Links    UID  GID  Size     Last Change              Name\n");
    printf("----------------------------------------------------------------------------------------\n");

    while (current != NULL) {
        // Rechte in richtiges Format formatieren
        format_rights(current->rights, rights);

        // Printed jede value die benötigt wird
        printf("%s %3d %4d %4d %s %s %s \n",
               rights,                   // Permissions
               current->count_hardlinks, // Hardlink Anzahl
               current->UserID,          // User ID
               current->groupID,         // Group ID
               current->temp_sizes,      // Größe der Datei
               current->lastChange,      // Zeit der letzten veränderung
               current->name             // Name der Datei oder des Verzeichnisses
        );

        current = current->next;
    }
}

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

