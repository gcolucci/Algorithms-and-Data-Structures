#include <stdlib.h>
#include <stdio.h>
#include "DoublyLinkedList.h"

/******************************************************
 ***************** MEMORY MANAGEMENT ******************
 ******************************************************/
 /**
 * Creates a new list node.
 *
 * It allocates space in the memory and initializes the
 * fields with a NULL pointer to the successor and predecessor
 * fields and with the info received by parameter.
 *
 * @param info: The int info stored by the node.
 * @return a pointer to the new node or NULL if memory
 * could not be allocated.
 */
Node *createNode(int info) {
    Node *newNode = (Node *) malloc(sizeof(Node));

    if (newNode) {
        newNode->next = newNode->previous = NULL;
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
 * @return the pointer to the modified list head.
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
    newNode->previous = p;

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
 * @return the pointer to the modified list head.
 */
Node *insertEndRecursive(Node *head, Node *newNode) {
    if (!head) {
        head = newNode;        
    }
    else if (head->next) {
        head->next = insertEndRecursive(head->next, newNode);
    }
    else {
        head->next = newNode;
        newNode->previous = head;
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
    head->previous = newNode;

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
        
        if (head) {
            head->previous = NULL;
        }     

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

        if (p1->next) {
            p1->next->previous = p1;
        }

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

    // Special case: head is to be removed.
    if (head->info == info) {
        p = head;
        head = head->next;

        if (head) {
            head->previous = NULL;
        }

        free(p);
        p = NULL;

        return head;
    }

    if (head->next && head->next->info == info) {
        p = head->next;
        head->next = p->next;

        if (head->next) {
            head->next->previous = head;
        }

        free(p);
        p = NULL;

        return head;
    }

    head->next = removeNodeRecursive(head->next, info);

    return head;
}

/**
 * Removes the last node from the list.
 *
 * It removes the last node from the list and returns the
 * modified list.
 *
 * @param head: A pointer to the list head.
 * @return The pointer to the modified list head.
 */
Node *removeLastNode(Node *head) {
    Node *p1, *p2;

    if (head) {
        p1 = head;
        p2 = head->next;

        // Special case: head is the only element.
        if (!p2) {
            free(p1);
            p1 = NULL;

            return NULL;
        }

        // Jumps to the end.
        while (p2->next) {
            p1 = p1->next;
            p2 = p2->next;
        }

        p1->next = NULL;

        free(p2);
        p2 = NULL;
    }

    return head;
}

/**
 * Recursively removes the last node from the list.
 *
 * It removes the last node from the list and returns the
 * modified list.
 *
 * @param head: A pointer to the list head.
 * @return The pointer to the modified list head.
 */
Node *removeLastNodeRecursive(Node *head) {
    if (head) {
        if (head->next) {
            head->next = lastNodeRecursive(head->next);
        }
        else {
            free(head);
            head = NULL;
        }
    }

    return head;
}

/**
 * Returns a pointer to the last node of the list.
 *
 * @param head: A pointer to the list head.
 * @return the pointer to the list last node.
 */
Node *lastNode(Node *head) {
    Node *p;

    if (!head) {
        return NULL;
    }

    p = head;
    while (p->next) {
        p = p->next;
    }

    return p;
}

/**
 * Recursively searches the last node of the list and
 * returns a pointer to it.
 *
 * @param head: A pointer to the list head.
 * @return the pointer to the list last node.
 */
Node *lastNodeRecursive(Node *head) {
    if (head && head->next) {
        return lastNodeRecursive(head->next);
    }

    return head;
}

/**
 * Returns a pointer to the last node of the list and
 * removes it from the list.
 *
 * @param head: A double pointer to the list head.
 * @return the pointer to the list last node.
 */
Node *popLastNode(Node **head) {
    Node *p1, *p2;

    if (*head) {
        p1 = *head;
        p2 = (*head)->next;

        // Special case: head is the only element.
        if (!p2) {
            *head = NULL;

            return p1;
        }

        // Jumps to the end.
        while (p2->next) {
            p1 = p1->next;
            p2 = p2->next;
        }

        p1->next = NULL;

        return p2;
    }

    return *head;
}

/**
 * Returns a pointer to the first node of the list and
 * removes it from the list.
 *
 * @param head: A double pointer to the list head.
 * @return the pointer to the list first node.
 */
Node *popFirstNode(Node **head) {
    Node *p;

    if (*head) {
        p = *head;
        *head = (*head)->next;

        if (*head) {
            (*head)->previous = NULL;
        }

        return p;
    }

    return *head;
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
void printList(Node *head) {
    Node *p, *pAux;

    if (head) {
        for(p = head; p; p = p->next) {
            printf("%d -> ", p->info);
            pAux = p;
        }
        printf("-\n");
    
        for(p = pAux; p; p = p->previous) {
            printf("%d -> ", p->info);
        }
    }
    printf("-\n");
}
