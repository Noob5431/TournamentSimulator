#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <cstring>

typedef struct Team Team;
typedef struct Player Player;

struct Team
{
    char *name;
    Player *players;

    Team *next;
};

struct Player
{
    char *firstName;
    char *secondName;
    int points;
    
    Player *next;
};

Team* team_add_element(Team *head,char *name);
Player* player_add_element(Player *head,char *firstName,char *lastName,int points);

#endif