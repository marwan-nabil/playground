#pragma once
#include <stdlib.h>
#include <stdbool.h>

#include "singly_linked_list.h"

struct queue {
    struct node_sll *front, *rear;
};

struct queue *create_queue();

void enqueue(struct queue *q, int value);
int dequeue(struct queue *q);
void print_queue(struct queue *q);
