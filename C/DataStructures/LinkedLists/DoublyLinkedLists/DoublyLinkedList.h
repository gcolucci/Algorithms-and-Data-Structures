#ifndef NODE_H
#define NODE_H

typedef struct node {
    struct node *next, *previous;
    int info;
} Node;

#endif // NODE_H

Node *createNode(int info);
void freeList(Node *head);
void freeListRecursive(Node *head);
Node *insertEnd(Node *head, Node *newNode);
Node *insertEndRecursive(Node *head, Node *newNode);
Node *insertBeginning(Node *head, Node *newNode);
Node *removeNode(Node *head, int info);
Node *removeNodeRecursive(Node *head, int info);
Node *removeLastNode(Node *head);
Node *removeLastNodeRecursive(Node *head);
Node *lastNode(Node *head);
Node *lastNodeRecursive(Node *head);
Node *popLastNode(Node **head);
Node *popFirstNode(Node **head);
void printList(Node *head);
void printListRecursive(Node *head);
