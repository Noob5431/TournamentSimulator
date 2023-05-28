#include <stdio.h>
#include <string.h>
#include "list.h"

char *read_name(FILE *input)
{
    char name_buffer[100],*name;

    fscanf(input,"%s",name_buffer);
    name = malloc(sizeof(char)*strlen(name_buffer)+1);
    strcpy(name,name_buffer);

    return name;
}

int main()
{
    FILE *input = fopen("d.in","r");
    if(input == NULL) exit(-1);

    Team *teams = NULL;
    int number_of_teams;

    fscanf(input,"%d",&number_of_teams);

    for(int i=0;i<number_of_teams;i++)
    {
        int number_of_players;
        fscanf(input,"%d",&number_of_players);

        char *team_name = read_name(input);
        teams = team_add_element(teams,team_name);

        for(int j=0;j<number_of_players;j++)
        {
            char *player_lname = read_name(input);
            char *player_fname = read_name(input);

            int points;
            fscanf(input,"%d",&points);

            teams->players = player_add_element(teams->players,player_fname,player_lname,points);
        }
    }

    print_teams(teams,1);
    delete_teams(teams);
    fclose(input);
}