#include "queue.h"
/*
* implementation of a queue for storing pointers
*
* created by Andrew Zelano and Isaac Pontarelli 2/14/20
*/


// nodes for the internal storage of the queue
struct Node{
    Node* next;
    Node* prev;
    int* elem;
};

// struct to store the head and tail of the queue
struct Queue{
    Node* head;
    Node* tail;
};

// function to generate a new queue
Queue* Queue_new(){
    Queue* q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

// emptys and then frees queue
void Queue_free(Queue* q){
    while (q->head != NULL){
        int* elem = Queue_pop(q);
        (void) elem;
    }
    free(q); 
}

// getter for first element
Node* Queue_getHead(Queue* q){
    return q->head;
}

// getter for last element
Node* Queue_getTail(Queue* q){
    return q->tail;
}

// add new element to end of queue
void Queue_append(Queue* q, int* elem){
    Node* n = malloc(sizeof(Node));
    n->elem = elem;
    n->next = NULL;
    // if queue is empty
    if (Queue_getTail(q) == NULL){
        q->head = n;
        q->tail = n;
        n->prev = NULL;
    }
    else{
        q->tail->next = n;
        q->tail = n;
        n->prev = q->tail;
    }
}

// remove the first node in the queue and return its data
int* Queue_pop(Queue* q){
    // test for empty queue
    if (q->head == NULL)
        return NULL;
    // test  if only one element left in queue
    if (q->head == q->tail){
        q->tail = NULL;
    }
    Node* temp = q->head;
    q->head = q->head->next;
    int* elem = temp->elem;
    free(temp);
    return elem;
}
