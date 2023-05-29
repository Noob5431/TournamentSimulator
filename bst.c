#include "bst.h"
#include "list.h"

void bst_create(bstElement **head,Team *value)
{
    (*head) = malloc(sizeof(bstElement));
    (*head)->left = NULL;
    (*head)->right = NULL;
    (*head)->team = value;
}

int bst_add(bstElement *head,Team *value)
{
    if(head == NULL) return -1;

    if(team_score(value) == team_score(head->team))
    {
        if(strcmp(value->name,head->team->name) < 0)
        {
            Team *temp = value;
            value = head->team;
            head->team = temp;
        }

    }
    if(team_score(value) < team_score(head->team))
    {
        if(head->left == NULL)
            bst_create(&head->left,value);
        else bst_add(head->left,value);
    }
    else
    {
        if(head->right == NULL)
            bst_create(&head->right,value);
        else bst_add(head->right,value);
    }
    return 0;
}

void print_spaces_bst(int count,FILE *output)
{
    for(int i=0;i<count;i++)
    {
        fprintf(output," ");
    }
}

int print_team(FILE *output,Team *team)
{
    int line_mark = 34;

    fprintf(output,"%s",team->name);
    int spaces = line_mark - strlen(team->name);
    print_spaces_bst(spaces,output);
    fprintf(output,"-  %.2f\n",team_score(team));
}

int print_bst_de(FILE *output,bstElement *head)
{
    if(head == NULL) return -1;

    print_bst_de(output,head->right);
    print_team(output,head->team);
    print_bst_de(output,head->left);

    return 0;
}

Team* bst_to_list(bstElement *head)
{
    Team *list = NULL;

    bst_to_list_rec(head,&list);
    return list;
}

int bst_to_list_rec(bstElement *current_element, Team **list)
{
    if(current_element == NULL) return -1;
    bst_to_list_rec(current_element->right,list);

    char *name = malloc(sizeof(char)*strlen(current_element->team->name)+1);
    strcpy(name,current_element->team->name);
    *list = team_add_element(*list,name);
    (*list)->players = copy_team(current_element->team->players);

    bst_to_list_rec(current_element->left,list);

    return 0;
}

bstElement* list_to_avl_rec(Team *list,int left,int right)
{
    if(left > right) return NULL;
    int half_point_index = left+(right-left)/2;
    if((right-left)%2!=0) half_point_index +=1;
    Team *half_point = team_at_index(list,half_point_index);

    bstElement *new_element = malloc(sizeof(bstElement));
    new_element->team = malloc(sizeof(Team));
    new_element->team->name = malloc(sizeof(char)*strlen(half_point->name)+1);
    strcpy(new_element->team->name,half_point->name);
    new_element->team->players = copy_team(half_point->players);
    new_element->team->next = NULL;

    new_element->right = list_to_avl_rec(list,left,half_point_index-1);
    new_element->left = list_to_avl_rec(list,half_point_index+1,right);

    return new_element;
}

int print_avl_level2(FILE *output,bstElement* node,int index)
{
    if(node == NULL) return -1;

    print_avl_level2(output,node->left,index+1);
    if(index == 2)
    {
        fprintf(output,"%s\n",node->team->name);
    }
    print_avl_level2(output,node->right,index+1);
    return 0;
}

int delete_bst(bstElement *node)
{
    if(node == NULL) return -1;

    bstElement *left,*right;
    left = node->left;
    right = node->right;

    delete_players(node->team->players);
    free(node->team->name);
    free(node->team);
    free(node);

    delete_bst(left);
    delete_bst(right);

    return 0;
}