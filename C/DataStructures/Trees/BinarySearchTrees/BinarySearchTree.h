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
void printBSTInOrder(Node *root);
void printBSTPreOrder(Node *root);
void printBSTPostOrder(Node *root);
void printBST(Node *root, int traverse);
