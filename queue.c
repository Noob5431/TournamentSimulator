#include "queue.h"

void enqueue(Queue **queue,Team *team1,Team *team2)
{
    if((*queue)==NULL)
    {
        *queue = malloc(sizeof(Queue));
        (*queue)->first = NULL;
        (*queue)->last = NULL;
    }

    QueueElement *new_queue_element = malloc(sizeof(QueueElement));
    new_queue_element->team1 = team1;
    new_queue_element->team2 = team2;
    new_queue_element->next = NULL;

    if((*queue)->first == NULL) (*queue)->first = new_queue_element;
    if((*queue)->last != NULL) (*queue)->last->next = new_queue_element;
    (*queue)->last = new_queue_element;

}

int dequeue(Queue *queue)
{
    if(queue->first == NULL) return -1;

    QueueElement *first = queue->first;
    queue->first = queue->first->next;
    if(first->next == NULL) queue->last = NULL;
    free(first);

    return 0;
}

void delete_queue(Queue *queue)
{
    QueueElement *current_element = queue->first;

    while(current_element)
    {
        QueueElement *temp = current_element;
        current_element = current_element->next;
        free(temp);
    }
    free(queue);
}

int queue_size(Queue *queue)
{
    QueueElement *current_element = queue->first;
    int size = 0;

    while(current_element)
    {
        size++;
        current_element = current_element->next;
    }

    return size;
}
