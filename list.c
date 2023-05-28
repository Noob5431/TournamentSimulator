#include <list.h>

Team *team_add_element(Team *head, char *name)
{
    Team *newTeam = (Team *)malloc(sizeof(Team));
    if(newTeam == NULL) exit(-1);

    newTeam->next = head;
    newTeam->players = NULL;
    strcpy(newTeam->name,name);

    return newTeam;
}

Player *player_add_element(Player *head, char *firstName, char *lastName, int points)
{
    Player *newPlayer = (Player *)malloc(sizeof(Player));
    if(newPlayer == NULL) exit(-1);

    newPlayer->next = head;
    strcpy(newPlayer->firstName, firstName);
    strcpy(newPlayer->secondName, lastName);
    newPlayer->points = points;
    head = newPlayer;

    return newPlayer;
}
