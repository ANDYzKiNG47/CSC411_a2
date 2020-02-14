#include "queue.h"

struct Node{
    Node* next;
    Node* prev;
    int* elem;
};

struct Queue{
    Node* head;
    Node* tail;
};

Queue* Queue_new(){
    Queue* q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void Queue_free(Queue* q){
    while (q->head != NULL){
        int* elem = Queue_pop(q);
        (void) elem;
    }
    free(q); 
}

Node* Queue_getHead(Queue* q){
    return q->head;
}

Node* Queue_getTail(Queue* q){
    return q->tail;
}
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

int* Queue_pop(Queue* q){
    if (q->head == NULL)
        return NULL;
    if (q->head == q->tail){
        q->tail = NULL;
    }
    Node* temp = q->head;
    q->head = q->head->next;
    int* elem = temp->elem;
    free(temp);
    return elem;
}
