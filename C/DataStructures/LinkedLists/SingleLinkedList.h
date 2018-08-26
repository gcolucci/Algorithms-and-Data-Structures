typedef struct node {
    struct node *next;
    int info;
} Node;

Node *createNode(int info);
void freeList(Node *head);
void freeListRecursive(Node *head);
Node *insertEnd(Node *head, Node *newNode);
Node *insertEndRecursive(Node *head, Node *newNode);
Node *insertBeginning(Node *head, Node *newNode);
Node *removeNode(Node *head, int info);
Node *removeNodeRecursive(Node *head, int info);
void print(Node *head);
void printRecursive(Node *head);
Node *reverseList(Node *head);
void reverseListRecursiveUtil(Node *head, Node *prev, Node **newHead);
Node *reverseListRecursive(Node *head);
