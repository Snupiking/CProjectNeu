#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "list.h"


Element *head = NULL;



void insert(char *param_name, int param_type, int param_size, int param_rights,
            int param_UserID, int param_GroupID, char *param_lastUse,
            char *param_lastChange, char *param_lastStatusChange, int count_hardlinks, char *param_path, char *temp_sizes)
{
    // Neues Element anlegen
    Element *newElement = (Element *)malloc(sizeof(Element));
    if (newElement == NULL) {
        perror("Memory allocation failed for newElement");
        exit(EXIT_FAILURE);
    }

    // Strings kopieren (sicherstellen, dass es nicht zu Speicherproblemen kommt)
    newElement->name = strdup(param_name);
    newElement->lastUse = strdup(param_lastUse);
    newElement->lastChange = strdup(param_lastChange);
    newElement->lastStatusChange = strdup(param_lastStatusChange);
    newElement->param_path = strdup(param_path);

    // Den Rest der Felder setzen
    newElement->type = param_type;
    newElement->size = param_size;
    newElement->temp_sizes = NULL;
    newElement->rights = param_rights;
    newElement->UserID = param_UserID;
    newElement->groupID = param_GroupID;
    newElement->count_hardlinks = count_hardlinks;

    // Liste verketten (Einfügen ans Ende)
    Element *curr = head;
    if (head == NULL) {
        head = newElement;  // Wenn die Liste leer ist, wird das neue Element der Kopf
        newElement->next = NULL;
    } else {
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newElement;  // Neues Element ans Ende anhängen
        newElement->next = NULL;
    }
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









