#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct element
{
    char *name; // Name der Datei/ des directories
    int type;   // File oder directory eigentlich besser als boolean->int bsp. true->dir false->file
    int size;   // groeße der Datei oder directory
    int rights;
    int UserID;
    int groupID;
    char* lastUse;
    char*lastChange;
    char* lastStatusChange;
    int count_hardlinks;
    struct element *next;

} Element;

static Element *head = NULL;



void insert(char *param_name, int param_type, int param_size,int param_rights,int param_UserID,
            int param_GroupID,char* param_lastUse,char* param_lastChange,char* param_lastStatusChange, int count_hardlinks)
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
void print_l() {
    Element *current = head;
    char rights[10];

    // Header
    printf("Permissions Links    UID  GID  Size     Last Change              Name\n");
    printf("----------------------------------------------------------------------------------------\n");

    while (current != NULL) {
        // Rechte in richtiges Format formatieren
        format_rights(current->rights, rights);

        // Printed jede value die benötigt wird
        printf("%s %3d %4d %4d %8d %s %s \n",
               rights,                   // Permissions
               current->count_hardlinks, // Hardlink Anzahl
               current->UserID,          // User ID
               current->groupID,         // Group ID
               current->size,            // Größe der Datei
               current->lastChange,      // Zeit der letzten veränderung
               current->name             // Name der Datei oder des Verzeichnisses
        );

        current = current->next;
    }
}
