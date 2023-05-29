#ifndef BST_H
#define BST_H
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct bstElement bstElement;

struct bstElement
{
    bstElement *left,*right;
    Team *team;
};

void bst_create(bstElement **head,Team *value);
int bst_add(bstElement *head,Team *value);
void print_spaces_bst(int count,FILE *output);
int print_team(FILE *output,Team *team);
int print_bst_de(FILE *output,bstElement *head);
Team* bst_to_list(bstElement *head);
int bst_to_list_rec(bstElement *current_element, Team **list);
bstElement* list_to_avl_rec(Team *list,int left,int right);
int print_avl_level2(FILE *output,bstElement* node,int index);
int delete_bst(bstElement *node);

#endif