#include <stdlib.h>
#include <stdio.h>

#include "Queue.h"

/******************************************************
 ***************** MEMORY MANAGEMENT ******************
 ******************************************************/
 /**
 * Creates a new queue.
 *
 * It takes a pointer to a Queue and sets its rear and front
 * to NULL.
 *
 * @param q: A pointer to the queue.
 */
void createQueue(Queue *q) {
    if (q) {
        q->data = q->front = q->rear = NULL;
    }
}

/**
 * Frees the memory used by the queue.
 *
 * @param q: A pointer to the queue.
 */
void freeQueue(Queue *q) {
    freeList(q->data);
}

/******************************************************
 ***************** BASIC OPERATIONS *******************
 ******************************************************/
/**
 * Enqueue a new element.
 *
 * It takes a new element to be queued, stores it in a Node
 * and inserts it in the beginning of the data linked list.
 * It positions the rear pointer to the new element. If it is
 * the first element in the queue, also positions the front
 * pointer.
 *
 * @param q: A pointer to the queue.
 * @param info the element to be enqueued.
 * @return 1 if it was successfully enqueued, 0 otherwise.
 */
int enqueue(Queue *q, int info) {
    Node *newNode = createNode(info);

    if (newNode) {
        // Insert new node in the beginning of the queue.
        q->data = insertBeginning(q->data, newNode);

        // Updates rear to the new element.
        q->rear = q->data;

        // Special case: first insertion.
        if (!q->front) {
            q->front = q->data;
        }

        return 1;
    }

    return 0;
}

/**
 * Dequeue the first element.
 *
 * It removes the front element from the queue and returns
 * it. It also appropriately updates the rear and front pointers.
 *
 * @param q: A pointer to the queue.
 * @return the front node.
 */
Node *dequeue(Queue *q) {
    Node *front;

    if (!q) {
        return NULL;
    }

    // Dequeue last node in the linked list (the queue front node).
    front = popLastNode(&(q->data));

    // Adjust front pointer.
    q->front = lastNode(q->data);

    return front;
}

/******************************************************
 ***************** OUTPUT *****************************
 ******************************************************/
/**
 * Prints a representation of the queue.
 *
 * It uses the -> symbols to represent the precedence of
 * two nodes.
 *
 * @param q: The queue.
 */
void printQueue(Queue q) {
    printList(q.data);
}
