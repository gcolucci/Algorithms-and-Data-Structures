#include <stdlib.h>
#include <stdio.h>
#include "SingleLinkedList.h"

/******************************************************
 ***************** MEMORY MANAGEMENT ******************
 ******************************************************/
 /**
 * Creates a new list node.
 *
 * It allocates space in the memory and initializes the
 * fields with a NULL pointer to the successor and the
 * info received by parameter.
 *
 * @param info: The int info stored by the node.
 * @return a pointer to the new node or NULL if memory
 * could not be allocated.
 */
Node *createNode(int info) {
    Node *newNode = (Node *) malloc(sizeof(Node));

    if (newNode) {
        newNode->next = NULL;
        newNode->info = info;
    }

    return newNode;
}

/**
 * Frees the memory used by list nodes.
 *
 * @param head: A pointer to the list head.
 */
void freeList(Node *head) {
    Node *p;

    while(head) {
        p = head;
        head = head->next;
        free(p);
        p = NULL;
    }
}

/**
 * Recursively frees the memory used by list nodes.
 *
 * @param head: A pointer to the list head.
 */
void freeListRecursive(Node *head) {
    if (head) {
        freeListRecursive(head->next);
        free(head);
        head = NULL;
    }
}

/******************************************************
 ***************** BASIC OPERATIONS *******************
 ******************************************************/
/**
 * Inserts a new node in the end of the list.
 *
 * It assumes that the node already has memory already
 * allocated and that the list pointed by head contains
 * nodes with correct pointers to next elements. It does
 * not perform any validation in the new node fields.
 *
 * @param head: A pointer to the list head.
 * @param newNode: A pointer to the node to be inserted.
 * @return The pointer to the modified list head.
 */
Node *insertEnd(Node *head, Node *newNode) {
    Node *p;

    // If the list is empty, creates a new head using the node to be inserted.
    if (!head) {
        head = newNode;
        return head;
    }

    // Traverses the list searching for its end.
    p = head;
    while (p->next) {
        p = p->next;
    }

    // Inserts node in the end.
    p->next = newNode;

    return head;
}

/**
 * Recursively inserts a new node in the end of the list.
 *
 * It assumes that the node already has memory already
 * allocated and that the list pointed by head contains
 * nodes with correct pointers to next elements. It does
 * not perform any validation in the new node fields.
 *
 * @param head: A pointer to the list head.
 * @param newNode: A pointer to the node to be inserted.
 * @return The pointer to the modified list head.
 */
Node *insertEndRecursive(Node *head, Node *newNode) {
    if (!head) {
        head = newNode;
    }
    else {
        head->next = insertEndRecursive(head->next, newNode);
    }

    return head;
}

/**
 * Inserts a new node in the beginning of the list.
 *
 * It assumes that the node already has memory already
 * allocated and that the list pointed by head contains
 * nodes with correct pointers to next elements. It does
 * not perform any validation in the new node fields.
 *
 * @param head: A pointer to the list head.
 * @param newNode: A pointer to the node to be inserted.
 * @return The pointer to the modified list head.
 */
Node *insertBeginning(Node *head, Node *newNode) {
    // If the list is empty, creates a new head using the node to be inserted.
    if (!head) {
        head = newNode;
        return head;
    }

    // Inserts node in the beginning.
    newNode->next = head;

    return newNode;
}

/**
 * Removes a node from the list, according to its info value.
 *
 * It searches for the first occurrence of a node that contains
 * the given value in its info field and deletes it, also freeing
 * the memory. If there is more than one node with the same info,
 * it removes the first occurrence. If there is no occurrence,
 * returns the list as-is.
 *
 * @param head: A pointer to the list head.
 * @param info: The value of the info to be removed.
 * @return The pointer to the modified list head.
 */
Node *removeNode(Node *head, int info) {
    Node *p1, *p2;

    // If the list is empty.
    if (!head) {
        return NULL;
    }

    // Special case: node to be deleted is the head.
    if (head->info == info) {
        p1 = head;
        head = head->next;

        free(p1);
        p1 = NULL;

        return head;
    }

    // Searches for the provided value.
    p2 = head;
    while (p2->info != info && p2->next) {
        p1 = p2;
        p2 = p2->next;
    }

    // Deletes the node, if found.
    if (p2->info == info) {
        p1->next = p2->next;

        free(p2);
        p2 = NULL;
    }

    return head;
}

/**
 * Recursively removes a node from the list, according to its info value.
 *
 * It searches for the first occurrence of a node that contains
 * the given value in its info field and deletes it, also freeing
 * the memory. If there is more than one node with the same info,
 * it removes the first occurrence. If there is no occurrence,
 * returns the list as-is.
 *
 * @param head: A pointer to the list head.
 * @param info: The value of the info to be removed.
 * @return The pointer to the modified list head.
 */
Node *removeNodeRecursive(Node *head, int info) {
    Node *p;

    if (!head) {
        return NULL;
    }

    if (head->info == info) {
        p = head->next;

        free(head);
        head = NULL;

        return p;
    }

    head->next = removeNodeRecursive(head->next, info);

    return head;
}

/******************************************************
 ***************** OUTPUT *****************************
 ******************************************************/
/**
 * Prints a representation of the list.
 *
 * It uses the -> symbols to represent the link between
 * two nodes. Null nodes are represented with -.
 *
 * @param head: A pointer to the list head.
 */
void print(Node *head) {
    Node *p;

    for(p = head; p; p = p->next) {
        printf("%d -> ", p->info);
    }
    printf("-\n");
}

/**
 * Recursively prints a representation of the list.
 *
 * It uses the -> symbols to represent the link between
 * two nodes. Null nodes are represented with -.
 *
 * @param head: A pointer to the list head.
 */
void printRecursive(Node *head) {
    Node *p;

    if (!head) {
        printf("-\n");
    }
    else {
        printf("%d -> ", head->info);
        printRecursive(head->next);
    }
}

/******************************************************
 ***************** ADVANCED OPERATIONS ****************
 ******************************************************/
/**
 * Reverses the order of a list nodes.
 *
 * It changes the direction of next pointers of all nodes,
 * making them point to their predecessors.
 *
 * @param head: A pointer to the list head.
 */
Node *reverseList(Node *head) {
    Node *pLeft, *pMiddle, *pRight;

    // Special cases: empty list and list containing only 1 node
    if (!head || !head->next) {
        return head;
    }

    pLeft = pRight = NULL;
    pMiddle = head;

    // At each iteration, it reverses the pointer of the middle node.
    // All nodes appearing before the middle are already reversed.
    while (pMiddle) {
        // Advances the rightmost pointer. It must be done in the beginning
        // of the loop to avoid segmentation fault.
        pRight = pMiddle->next;

        // Reverses the middle pointer.
        pMiddle->next = pLeft;

        // Advances the other pointers.
        pLeft = pMiddle;
        pMiddle = pRight;
    }

    return pLeft;
}

/**
 * Effectively reverses the order of a list nodes.
 *
 * @param head: A pointer to the list head.
 * @param prev: A pointer to the list predecessor.
 * @param newHead: A pointer to store the list updated head.
 */
void reverseListRecursiveUtil(Node *head, Node *prev, Node **newHead) {
    if (!head->next) {
        head->next = prev;
        *newHead = head;
    }
    else {
        reverseListRecursiveUtil(head->next, head, newHead);
        head->next = prev;
    }
}

/**
 * Recursively reverses the order of a list nodes.
 *
 * It changes the direction of next pointers of all nodes,
 * making them point to their predecessors.
 *
 * @param head: A pointer to the list head.
 */
Node *reverseListRecursive(Node *head) {
    Node *newHead;

    if (!head) {
        return NULL;
    }

    newHead = NULL;
    reverseListRecursiveUtil(head, NULL, &newHead);

    return newHead;
}
