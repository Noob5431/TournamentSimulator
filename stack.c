#include "stack.h"

void stack_add(StackElement **head, Team *team)
{
    StackElement *new_stack_element = malloc(sizeof(StackElement));

    new_stack_element->next = *head;
    (*head) = new_stack_element;

    new_stack_element->team = team;
}

Team* stack_pop(StackElement **head)
{
    StackElement *temp = *head;
    Team *team = (*head)->team;
    *head = (*head)->next;
    
    free(temp);
    return team;
}

void delete_stack(StackElement **head)
{
    while (*head)
    {
        StackElement *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int stack_size(StackElement *head)
{
    int size = 0;

    while(head)
    {
        size++;
        head = head->next;
    }

    return size;
}