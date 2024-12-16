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
    struct element *next;

} Element;

static Element *head = NULL;

void insertAtHead(char *param_name, int param_type, int param_size)
{

    Element *newElement = (Element *)malloc(sizeof(Element));
    newElement->name = param_name;
    newElement->type = param_type;
    newElement->size = param_size;

    if (head == NULL)
    {
        newElement->next = NULL;
        head = newElement;
        return;
    }

    newElement->next = head;
    head = newElement;
}

void insert(char *param_name, int param_type, int param_size)
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

    delete ();
    delete ();
    delete ();
    delete ();
    delete ();
    printList(head);
    return 0;
}