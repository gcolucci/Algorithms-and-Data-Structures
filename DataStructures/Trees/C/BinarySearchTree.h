#define IN_ORDER 1
#define PRE_ORDER 2
#define POST_ORDER 3

typedef struct node {
    struct node *left, *right;
    int info;
} Node;

Node *createNode(int info);
void freeTree(Node *root);
Node *insertNode(Node *root, Node *newNode);
Node *removeNode(Node *root, int info);
void printInOrder(Node *root);
void printPreOrder(Node *root);
void printPostOrder(Node *root);
void print(Node *root, int traverse);
