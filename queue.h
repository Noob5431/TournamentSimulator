#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef struct Queue Queue;
typedef struct QueueElement QueueElement;

struct Queue
{
    QueueElement *first,*last;
};

struct QueueElement
{
    QueueElement *next;
    Team *team1,*team2;
};

int dequeue(Queue *queue);
void enqueue(Queue **queue,Team *team1,Team *team2);
void delete_queue(Queue *queue);
int queue_size(Queue *queue);

#endif