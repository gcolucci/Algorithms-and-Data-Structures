#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"

/******************************************************
 ***************** MEMORY MANAGEMENT ******************
 ******************************************************/
 /**
 * Creates a new tree node.
 *
 * It allocates space in the memory and initializes the
 * fields with a NULL pointer to the children and the
 * info received by parameter.
 *
 * @param info: The int info stored by the node.
 * @return a pointer to the new node or NULL if memory
 * could not be allocated.
 */
Node *createNode(int info) {
    Node *newNode = (Node *) malloc(sizeof(Node));

    if (newNode) {
        newNode->left = newNode->right = NULL;
        newNode->info = info;
    }

    return newNode;
}

/**
 * Frees the memory used by tree nodes.
 *
 * @param root: A pointer to the tree root.
 */
void freeTree(Node *root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);

        free(root);
        root = NULL;
    }
}

/******************************************************
 ***************** BASIC OPERATIONS *******************
 ******************************************************/
/**
 * Inserts a new node in the tree.
 *
 * It follows the convention of lesser or equal elements
 * to the left of the root and greater elements to the
 * right. It does not perform any validation in the new node fields.
 *
 * @param root: A pointer to the tree root.
 * @param newNode: A pointer to the node to be inserted.
 * @return The pointer to the modified tree root.
 */
Node *insertNode(Node *root, Node *newNode) {
    if (!root) {
        return newNode;
    }

    if (newNode->info <= root->info) {
        root->left = insertNode(root->left, newNode);
    }
    else if (newNode->info > root->info) {
        root->right = insertNode(root->right, newNode);
    }

    return root;
}

/**
 * Removes a node from the tree, according to its info value.
 *
 * It searches for the first occurrence of a node that contains
 * the given value in its info field and deletes it, also freeing
 * the memory. If there is more than one node with the same info,
 * it removes the first occurrence. If there is no occurrence,
 * returns the tree as-is.
 *
 * @param root: A pointer to the tree root.
 * @param info: The value of the info to be removed.
 * @return The pointer to the modified tree root.
 */
Node *removeNode(Node *root, int info) {
    Node *p, *pParent;

    if (!root) {
        return NULL;
    }

    if (info < root->info) {
        root->left = removeNode(root->left, info);

        return root;
    }
    if (info > root->info) {
        root->right = removeNode(root->right, info);

        return root;
    }

    // If root is the node to be removed.

    // If it has no left children, just append the right
    // subtree to its parent.
    if (!root->left) {
        p = root->right;

        free(root);
        root = NULL;

        return p;
    }

    // Conversely, if it has no right children.
    if (!root->right) {
        p = root->left;

        free(root);
        root = NULL;

        return p;
    }

    // If it has both, it must be replaced by either
    // the greatest of its left children or the
    // smallest of its right children. This code takes
    // the first approach.

    // Places a pointer in the root of the left subtree.
    pParent = root->left;

    // If pParent has no right children, than pParent
    // itself should replace the deleted root.
    if (!pParent->right) {
        // p will point to the node that will replace the
        // deleted root.
        p = pParent;
    }
    else {
        // Otherwise, pParent now will hold a pointer to
        // the parent of the node that will replace the
        // deleted root.

        // Searches for the greatest children of pParent
        // right subtree.
        p = pParent->right;
        while(p->right) {
            pParent = p;
            p = pParent->right;
        }

        // Adjust pointers
        pParent->right = p->left;
        p->left = root->left;
    }

    p->right = root->right;

    free(root);
    root = NULL;

    return p;
}

/******************************************************
 ***************** OUTPUT *****************************
 ******************************************************/
/**
 * Prints an in-order representation of the tree.
 *
 * It displays a parenthesized representation of the tree,
 * traversing it in-order.
 *
 * @param root: A pointer to the tree root.
 */
void printInOrder(Node *root) {
    if (root) {
        printf("(");
        printInOrder(root->left);
        printf(")");

        printf("%d", root->info);

        printf("(");
        printInOrder(root->right);
        printf(")");
    }
}

/**
 * Prints an pre-order representation of the tree.
 *
 * It displays a parenthesized representation of the tree,
 * traversing it pre-order.
 *
 * @param root: A pointer to the tree root.
 */
void printPreOrder(Node *root) {
    if (root) {
        printf("%d", root->info);

        printf("(");
        printInOrder(root->left);
        printf(")");

        printf("(");
        printInOrder(root->right);
        printf(")");
    }
}

/**
 * Prints an post-order representation of the tree.
 *
 * It displays a parenthesized representation of the tree,
 * traversing it post-order.
 *
 * @param root: A pointer to the tree root.
 */
void printPostOrder(Node *root) {
    if (root) {
        printf("(");
        printInOrder(root->left);
        printf(")");

        printf("(");
        printInOrder(root->right);
        printf(")");

        printf("%d", root->info);
    }
}

/**
 * Auxiliary function to trigger the appropriate representation
 * of the tree.
 *
 * @param root: A pointer to the tree root.
 * @param traverse: An int representing the order in which the tree,
 * using the defined constants: IN_ORDER, PRE_ORDER, AND POST_ORDER.
 */
void print(Node *root, int traverse) {
    switch(traverse) {
        case IN_ORDER:
            printInOrder(root);
            break;
        case PRE_ORDER:
            printPreOrder(root);
            break;
        case POST_ORDER:
            printPostOrder(root);
    }

    printf("\n");
}
