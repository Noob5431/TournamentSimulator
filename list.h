#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void delete_players(Player *head);
void delete_teams(Team *head);
void print_players(Player *head);
void print_teams(Team *head,int printPlayers);
#endif