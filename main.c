#include <stdio.h>
#include <string.h>
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "bst.h"

int is_2power(int a)
{
    if (a < 1 || a % 2 != 0)
        return 0;
    while (a % 2 == 0)
    {
        a /= 2;
    }
    if (a == 1)
        return 1;
    else
        return 0;
}

int closest_2power(int a)
{
    for (; a > 0; a--)
    {
        if (is_2power(a))
            return a;
    }
}

char *read_team_name(FILE *input)
{
    char name_buffer[100], *name;
    char c = ' ';

    while (c == ' ')
    {
        fscanf(input, "%c", &c);
    }
    int i = 0;
    while (c != '\n' && c != EOF)
    {
        name_buffer[i] = c;
        i++;
        fscanf(input, "%c", &c);
    }
    name_buffer[i] = '\0';
    i--;
    while(name_buffer[i]==' ')
        name_buffer[i] = '\0';
    name = malloc(sizeof(char) * strlen(name_buffer) + 1);
    strcpy(name, name_buffer);

    return name;
}

char *read_name(FILE *input)
{
    char name_buffer[100], *name;

    fscanf(input, "%s", name_buffer);
    name = malloc(sizeof(char) * strlen(name_buffer) + 1);
    strcpy(name, name_buffer);

    return name;
}

void play_match(QueueElement *match, StackElement **winners, StackElement **losers)
{

    float score1 = team_score(match->team1);
    float score2 = team_score(match->team2);

    if (score2 >= score1)
    {
        stack_add(winners, match->team2);
        stack_add(losers, match->team1);
    }
    else
    {
        stack_add(winners, match->team1);
        stack_add(losers, match->team2);
    }

    add_score((*winners)->team->players,1);
}

void play_round(Queue *matches, StackElement **winners, StackElement **losers)
{
    while (matches->first)
    {
        play_match(matches->first, winners, losers);
        dequeue(matches);
    }
}

void prepare_round(Queue **matches, StackElement **winners, StackElement **losers)
{
    delete_stack(losers);
    while ((*winners))
    {
        enqueue(matches, (*winners)->team, (*winners)->next->team);
        stack_pop(winners);
        stack_pop(winners);
    }
}

void save_round(Team **save, Queue *matches)
{
    QueueElement *current_match = matches->first;
    while (current_match)
    {
        *save = team_add_element(*save, current_match->team1->name);
        (*save)->players = copy_team(current_match->team1->players);
        *save = team_add_element(*save, current_match->team2->name);
        (*save)->players = copy_team(current_match->team2->players);
        current_match = current_match->next;
    }
}

void print_spaces(int count,FILE *output)
{
    for(int i=0;i<count;i++)
    {
        fprintf(output," ");
    }
}

void print_round(Queue *matches, int index,FILE *output)
{
    int line_mark = 33,line_end_mark = 67;

    fprintf(output,"\n--- ROUND NO:%d\n",index);
    QueueElement *current_match = matches->first;
    
    while(current_match)
    {
        fprintf(output,"%s",current_match->team1->name);
        int spaces = line_mark - strlen(current_match->team1->name);
        print_spaces(spaces,output);
        fprintf(output,"-");

        spaces = line_end_mark - strlen(current_match->team2->name) - 1 - line_mark;
        print_spaces(spaces,output);
        fprintf(output,"%s\n",current_match->team2->name);
        current_match = current_match->next;
    }
}

void print_winners(StackElement *winners,int index,FILE *output)
{
    int line_mark = 34;
    fprintf(output,"\nWINNERS OF ROUND NO:%d\n",index);

    while(winners)
    {
        //fprintf(output,"%s                 -  %.2f\n",winners->team->name,team_score(winners->team));
        fprintf(output,"%s",winners->team->name);
        int spaces = line_mark - strlen(winners->team->name);
        print_spaces(spaces,output);
        fprintf(output,"-  %.2f\n",team_score(winners->team));
        winners = winners->next;
    }
}

int main(int argc, char *argv[])
{
    FILE *tasks = fopen(argv[1], "r");
    FILE *input = fopen(argv[2], "r");
    FILE *output = fopen(argv[3], "w");
    if (tasks == NULL || input == NULL || output == NULL)
        exit(-1);
    // FILE *input = fopen("d.in","r");
    // FILE *output = fopen("d.out","w");

    int c1, c2, c3, c4, c5;
    fscanf(tasks, "%d%d%d%d%d", &c1, &c2, &c3, &c4, &c5);
    Team *teams = NULL;
    int number_of_teams = 0;

    // read teams
    fscanf(input, "%d", &number_of_teams);
    for (int i = 0; i < number_of_teams; i++)
    {
        int number_of_players;
        fscanf(input, "%d", &number_of_players);
        char *team_name = read_team_name(input);
        teams = team_add_element(teams, team_name);

        for (int j = 0; j < number_of_players; j++)
        {
            char *player_lname = read_name(input);
            char *player_fname = read_name(input);

            int points;
            fscanf(input, "%d", &points);

            teams->players = player_add_element(teams->players, player_fname, player_lname, points);
        }
    }

    if (c1 && !c2)
        print_teams(teams, 0, output);

    if (c2)
    {
        int n = closest_2power(number_of_teams);

        int to_delete = number_of_teams - n;

        for (; to_delete > 0; to_delete--)
        {
            remove_worst_team(&teams);
        }
        print_teams(teams, 0, output);
    }

    Queue *matches = NULL;
    Team *first8 = NULL;
    if (c3)
    {
        
        Team *current_team = teams;

        while (current_team)
        {
            enqueue(&matches, current_team, current_team->next);
            current_team = current_team->next->next;
        }

        StackElement *winners = NULL, *losers = NULL;
        int nr_of_matches  = queue_size(matches);
        int round_index = 1;
        
        while (nr_of_matches > 0)
        {
            print_round(matches,round_index,output);
            play_round(matches, &winners, &losers);
            print_winners(winners,round_index,output);
            if(nr_of_matches>1)
                prepare_round(&matches, &winners, &losers);
            round_index++;

            if(nr_of_matches == 8)
            {
                save_round(&first8,matches);
            }
            nr_of_matches  = queue_size(matches);
        }
    }

    bstElement *bst = NULL;
    if(c4)
    {
        fprintf(output,"\nTOP 8 TEAMS:\n");
        
        bst_create(&bst,first8);
        
        first8 = first8->next;
        while(first8)
        {
            bst_add(bst,first8);
            first8 = first8->next;
        }
        print_bst_de(output,bst);
    }

    bstElement *avl = NULL;
    Team *first8_list = NULL;
    if(c5)
    {
        first8_list = bst_to_list(bst);
        avl = list_to_avl_rec(first8_list,0,team_size(first8_list)-1);

        fprintf(output,"\nTHE LEVEL 2 TEAMS ARE:\n");
        print_avl_level2(output,avl,0);
    }

    // free memory
    if (c3)
        delete_queue(matches);
    if(c4)
    {
        delete_bst(bst);
        delete_teams(first8);
    }
    if(c5)
    {
        delete_bst(avl);
        delete_teams(first8_list);
    }
    
    delete_teams(teams);
    fclose(tasks);
    fclose(input);
    fclose(output);
}