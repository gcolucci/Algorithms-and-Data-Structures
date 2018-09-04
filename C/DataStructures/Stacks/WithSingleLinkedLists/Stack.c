#include <stdlib.h>
#include <stdio.h>

#include "Stack.h"

/******************************************************
 ***************** MEMORY MANAGEMENT ******************
 ******************************************************/
 /**
 * Creates a new stack.
 *
 * It takes a pointer to a Stack and sets its rear and front
 * to NULL.
 *
 * @param s: A pointer to the stack.
 */
void createStack(Stack *s) {
    if (s) {
        s->data = s->front = NULL;
    }
}

/**
 * Frees the memory used by the stack.
 *
 * @param q: A pointer to the stack.
 */
void freeStack(Stack *s) {
    freeList(s->data);
}

/******************************************************
 ***************** BASIC OPERATIONS *******************
 ******************************************************/
/**
 * Pushes a new element.
 *
 * It takes a new element to be stacked, stores it in a Node
 * and inserts it in the beginning of the data linked list.
 * It positions the front pointer to the new element.
 *
 * @param s: A pointer to the stack.
 * @param info the element to be stacked.
 * @return 1 if it was successfully stacked, 0 otherwise.
 */
int push(Stack *s, int info) {
    Node *newNode = createNode(info);

    if (newNode) {
        // Insert new node in the beginning of the stack.
        s->front = s->data = insertBeginning(s->data, newNode);

        return 1;
    }

    return 0;
}

/**
 * Pops the first element.
 *
 * It removes the front element from the stack and returns
 * it. It also appropriately updates the front pointers.
 *
 * @param s: A pointer to the stack.
 * @return the front node.
 */
Node *pop(Stack *s) {
    Node *front;

    if (!s) {
        return NULL;
    }

    // Pops first node in the linked list (the stack top).
    front = popFirstNode(&(s->data));

    // Adjust front pointer.
    s->front = s->data;

    return front;
}

/******************************************************
 ***************** OUTPUT *****************************
 ******************************************************/
/**
 * Prints a representation of the stack.
 *
 * It uses the -> symbols to represent the precedence of
 * two nodes.
 *
 * @param s: The stack.
 */
void printStack(Stack s) {
    printList(s.data);
}
