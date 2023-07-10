#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "queue.h"
#include "array.h"
#include "singly_linked_list.h"

struct queue *create_queue()
{
    struct queue *new_queue = (struct queue *)malloc(sizeof(struct queue));
    new_queue->front = new_queue->rear = NULL;
    return new_queue;
}

void enqueue(struct queue *q, int value)
{
    struct node_sll *new_node = create_new_node_sll(value);

    if (q->front == NULL)
    {
        q->front = new_node;
    }
    else
    {
        q->rear->next = new_node;
    }

    q->rear = new_node;
    q->rear->next = q->front; // circular linked list
}

// pop the first element from the queue
int dequeue(struct queue *q)
{
    if (q->front == NULL)
    {
        printf("\nNOTE: the queue is empty\n");
        return 0;
    }

    int value;
    if (q->front == q->rear)
    {
        // this is the last node to be deleted
        value = q->front->data;
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
    }
    else // There are more than one nodes
    {
        struct node_sll *node_to_delete = q->front;
        value = node_to_delete->data;
        q->front = q->front->next;
        q->rear->next = q->front;
        free(node_to_delete);
    }

    return value;
}


void print_queue(struct queue *q)
{
    struct node_sll *current_node = q->front;
    printf("\nqueue elements are: ");
    while (current_node->next != q->front) // while we still haven't got to the last node
    {
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }
    // print the last node
    printf("%d\n", current_node->data);
}