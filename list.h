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
void print_players(Player *head,FILE *file);
void print_teams(Team *head,int printPlayers, FILE *file);
int remove_worst_team(Team **head);
float team_score(Team *team);
void add_score(Player *players, int to_add);
Player* copy_team(Player *player);
int team_size(Team *team);
Team* team_at_index(Team* teams,int index);
#endif