#include <list.h>

Team *team_add_element(Team *head, char *name)
{
    Team *newTeam = (Team *)malloc(sizeof(Team));
    if(newTeam == NULL) exit(-1);

    newTeam->next = head;
    newTeam->players = NULL;
    newTeam->name = name;

    return newTeam;
}

Player *player_add_element(Player *head, char *firstName, char *lastName, int points)
{
    Player *newPlayer = (Player *)malloc(sizeof(Player));
    if(newPlayer == NULL) exit(-1);

    newPlayer->next = head;
    newPlayer->firstName = firstName;
    newPlayer->secondName = lastName;
    //strcpy(newPlayer->firstName, firstName);
    //strcpy(newPlayer->secondName, lastName);
    newPlayer->points = points;
    head = newPlayer;

    return newPlayer;
}

void print_teams(Team *head,int printPlayers)
{
    if(head)
    {
        printf("%s\n",head->name);
        if(printPlayers)
        {
            print_players(head->players);
        }
        print_teams(head->next,print_players);
    }
}

void print_players(Player *head)
{
    if(head)
    {
        printf("--------%s %s %d\n",head->secondName,head->firstName,head->points);
        print_players(head->next);
    }
}

void delete_teams(Team *head)
{
    if(head)
    {
        free(head->name);

        Team *temp = head->next;
        free(head);
        delete_teams(temp);
    }
}

void delete_players(Player *head)
{
    if(head)
    {
        free(head->firstName);
        free(head->secondName);
    
        Player *temp = head->next;
        free(head);
        delete_players(temp);
    }
}