#include "../../LinkedLists/SingleLinkedLists/SingleLinkedList.h"

typedef struct {
    Node *data;
    Node *front;
} Stack;

void createStack(Stack *s);
void freeStack(Stack *s);
int push(Stack *s, int info);
Node *pop(Stack *s);
void printStack(Stack s);
