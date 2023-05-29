#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef struct StackElement StackElement;

struct StackElement
{
    Team *team;
    StackElement *next;
};

void stack_add(StackElement **head, Team *team);
Team* stack_pop(StackElement **head);
void delete_stack(StackElement **head);
int stack_size(StackElement *head);

#endif