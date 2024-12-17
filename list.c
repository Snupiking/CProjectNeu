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
    char* rights;
    int UserID;
    int groupID;
    struct element *next;

} Element;

static Element *head = NULL;



void insert(char *param_name, int param_type, int param_size,char* param_rights,int param_UserID, int param_GroupID)
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

void printList(Element *head)
{
    while (head != NULL)
    {
        printf("%s\n", head->name);
        head = head->next;
    }
}

int main(void)
{
    // test
    insert("hallo", 1, 50);
    insert("welt", 0, 40);
    insert("y", 5, 35);
    insert("t", 2, 40);
    insert("x", 4, 20);
    printList(head);
    delete ();
    delete ();
    delete ();
    delete ();
    delete ();
    printList(head);
    return 0;
}