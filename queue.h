#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct Queue Queue;
typedef struct Node Node;

Queue* Queue_new();

void Queue_free(Queue* q);

Node* Queue_getHead(Queue* q);

Node* Queue_getTail(Queue* q);

// places element in the back of the queue
void Queue_append(Queue* q, int* elem);

// removes and returns first element of the queue
int* Queue_pop(Queue* q);

#endif
