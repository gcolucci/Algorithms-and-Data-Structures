#include "../../LinkedLists/SinglyLinkedLists/SinglyLinkedList.h"

typedef struct {
    Node *data;
    Node *rear, *front;
} Queue;

void createQueue(Queue *q);
void freeQueue(Queue *q);
int enqueue(Queue *q, int info);
Node *dequeue(Queue *q);
void printQueue(Queue q);
