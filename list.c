#include "list.h"

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

void print_teams(Team *head,int printPlayers, FILE *file)
{
    if(head)
    {
        fprintf(file,"%s\n",head->name);
        if(printPlayers)
        {
            print_players(head->players,file);
        }
        print_teams(head->next,printPlayers,file);
    }
}

void print_players(Player *head,FILE *file)
{
    if(head)
    {
        fprintf(file,"--------%s %s %d\n",head->secondName,head->firstName,head->points);
        print_players(head->next,file);
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

float team_score(Team *team)
{
    float score = 0;
    int number_of_players=0;
    Player *current_player = team->players;

    while(current_player)
    {
        score+=current_player->points;
        number_of_players++;
        current_player = current_player->next;
    }
    if(number_of_players == 0) return 0;
    return score/number_of_players;
}

int remove_worst_team(Team **head)
{
    if(!(*head)) return -1;


    Team *current_team = *head;
    float smallest_score = team_score(*head);

    while(current_team)
    {
        float score = team_score(current_team);
        if(score<smallest_score)
            smallest_score = score;
        current_team = current_team->next;
    }

    current_team = *head;
    Team *last_team = *head;
    while(current_team)
    {
        if(team_score(current_team) == smallest_score)
        {
            if(current_team == *head)
            {
                *head = current_team->next;
            }
            else
            {
                last_team->next = current_team->next;
            }
            delete_players(current_team->players);
            free(current_team->name);
            free(current_team);
            return 0;
        }
        last_team = current_team;
        current_team = current_team->next;
    }

    return -1;
}

void add_score(Player *players, int to_add)
{
    while(players)
    {
        players->points += to_add;
        players = players->next;
    }
}

Player* copy_team(Player *player)
{
    Player *copy = NULL;

    while(player)
    {
        copy = player_add_element(copy,player->firstName,player->secondName,player->points);
        player = player->next;
    }

    return copy;
}

int team_size(Team *team)
{
    int size = 0;
    
    while(team)
    {
        size++;
        team = team->next;
    }

    return size;
}

Team* team_at_index(Team* teams,int index)
{
    if(index<0) return NULL;

    for(int i=0;i<index;i++)
    {
        teams = teams->next;
    }

    return teams;
}