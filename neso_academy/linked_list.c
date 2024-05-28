/**
 * Videos de linked list en neso academy... muy buenos
 */

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
};

int count_of_nodes(struct node *head);
void print_nodes(struct node *head);
void add_at_end(struct node *head, int data);
void add_at_beginning(struct node **head, int data);

int main()
{
    struct node *head = NULL;
    head = (struct node *)malloc(sizeof(struct node));

    head->data = 45;
    head->link = NULL;

    struct node *current = (struct node *)malloc(sizeof(struct node));
    current->data = 98;
    current->link = NULL;
    head->link = current;

    current = (struct node *)malloc(sizeof(struct node));
    current->data = 3;
    current->link = NULL;

    head->link->link = current;

    add_at_end(head, 99);
    add_at_end(head, 69);
    count_of_nodes(head);
    print_nodes(head);

    add_at_beginning(&head, 1);
    count_of_nodes(head);
    print_nodes(head);
    return 0;
}

void add_at_beginning(struct node **head, int data)
{
    struct node *ptr;

    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->link = *head;

    *head = ptr;
}

void add_at_end(struct node *head, int data)
{
    struct node *ptr, *temp;
    ptr = head;
    while (ptr->link != NULL)
    {
        ptr = ptr->link;
    }
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->link = NULL;

    ptr->link = temp;
}

int count_of_nodes(struct node *head)
{
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return 0;
    }

    struct node *ptr = head;
    int count = 0;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->link;
    }

    printf("\n\nNodes: %d\n", count);
    return count;
}

// creado por mi para debug
void print_nodes(struct node *head)
{
    if (head == NULL)
    {
        printf("The list is empty!\n");
        return;
    }

    struct node *current = head;
    printf("%-5s %-20s\n", "Data", "Link");

    while (current != NULL)
    {
        printf("%-5d %-20p\n", current->data, current->link);
        current = current->link;
    }
}