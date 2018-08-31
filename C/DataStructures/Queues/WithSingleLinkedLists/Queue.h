#include "SingleLinkedList.h"

typedef struct {
    Node *data;
    Node *rear, *front;
} Queue;

void createQueue(Queue *q);
void freeQueue(Queue *q);
void enqueue(Queue *q, int info);
void dequeue(Queue *q);
void printQueue(Queue q);
