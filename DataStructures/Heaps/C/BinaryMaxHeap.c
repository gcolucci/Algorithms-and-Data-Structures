#include <stdlib.h>
#include <stdio.h>
#include "BinaryMaxHeap.h"

/******************************************************
 ***************** MEMORY MANAGEMENT ******************
 ******************************************************/
 /**
 * Creates a new heap with pre-defined initial size.
 *
 * It allocates space in the memory to store the amount of
 * elements passed by parameter plus 1. The extra room is
 * to make indexed accesses to the heap easier. It also
 * initializes the counter of elements with 0 and its size to n.
 *
 * @param heap: A pointer to the heap structure to be initialized.
 * @param n: The initial size of the heap.
 * @return an int representing the success of the memory allocation.
 * It returns 0 in case of error and 1 in case of success.
 */
int createHeap(MaxHeap *heap, int n) {
    heap->info = (int *) malloc(sizeof(int) * (n+1));

    if (heap->info) {
        heap->n = 0;
        heap->size = n;

        return 1;
    }

    return 0;
}

/**
 * Frees the memory used by heap storage.
 *
 * @param heap: The heap which array of info is to be
 * freed.
 */
void freeHeap(MaxHeap *heap) {
    free(heap->info);
}

/******************************************************
 ***************** FIX OPERATIONS *********************
 ******************************************************/
/**
 * Fix the position of misplaced nodes in the path from the
 * k-th element to the heap root.
 *
 * Fixing the heap means to rearrange the elements so every
 * node in the path is greater or equal to all of its
 * descendants. It traverses the heap bottom-up and stops
 * when the first element in the correct position is found.
 * If the heap is updated using the functions hereby defined,
 * it is not necessary to check the whole path.
 *
 * @param heap: A pointer to the heap.
 * @param k: The index of the last element to be arranged.
 */
void fixUp(MaxHeap *heap, int k) {
    int aux;

    // Traverses the path
    while (k > 1 && heap->info[k] > heap->info[k/2]) {
        // Swaps elements.
        aux = heap->info[k];
        heap->info[k] = heap->info[k/2];
        heap->info[k/2] = aux;

        // Jumps to the parent.
        k /= 2;
    }
}

/**
 * Fix the position of misplaced nodes in the path from the
 * k-th to its last descendant.
 *
 * Fixing the heap means to rearrange the elements so every
 * node in the path is greater or equal to all of its
 * descendants. It traverses the heap top-down and stops
 * when the first element in the correct position is found.
 * If the heap is updated using the functions hereby defined,
 * it is not necessary to check the whole path.
 *
 * @param heap: A pointer to the heap.
 * @param k: The index of the first element to be arranged.
 */
void fixDown(MaxHeap *heap, int k) {
    int aux, n, i;

    n = heap->n;

    // Traverses the path.
    i = 2*k;
    while (i <= n) {
        // Chooses the greater sibling among k children.
        if (heap->info[i] < heap->info[i+1]) {
            i = i+1;
        }

        // Stops if it found an element in the correct place.
        if (heap->info[k] >= heap->info[i]) {
            break;
        }

        // Swaps elements.
        aux = heap->info[k];
        heap->info[k] = heap->info[i];
        heap->info[i] = aux;

        // Jumps to the swapped element and its left child.
        k = i;
        i *= 2;
    }
}

/******************************************************
 ***************** BASIC OPERATIONS *******************
 ******************************************************/
/**
 * Extracts the greatest element of the heap.
 *
 * It returns the maximum element of the heap and removes it from the
 * structure.
 *
 * @param heap: A pointer to the heap.
 * @return an int representing the maximum element or 0 if the heap is
 * empty.
 */
int extractMax(MaxHeap *heap) {
    int n, max;

    n = heap->n;

    // If heap is empty.
    if (n == 0) {
        return 0;
    }

    // Gets first element.
    max = heap->info[1];

    // Puts last element in the first position.
    heap->info[1] = heap->info[n];

    // Fix the heap.
    heap->n--;
    fixDown(heap, 1);

    return max;
}

/**
 * Inserts a new element in the heap.
 *
 * It assumes that the heap already has memory already
 * allocated and that all elements are correctly positioned
 * before the insertion. If the memory allocation must be expanded,
 * it increases it by 25%. If there is not enough memory for such
 * expansion, it does not verify if it is possible to expand it less.
 *
 * @param heap: A pointer to the heap.
 * @param elem: The new value to be inserted.
 * @return an int representing the success of the memory allocation.
 * It returns 0 in case of error and 1 in case of success.
 */
int insertHeap(MaxHeap *heap, int elem) {
    int *allocResult;

    // If the heap can't fit more elements
    if (heap->n == heap->size) {
        // Reallocates the memory for the elements array.
        allocResult = (int *) realloc(heap->info, sizeof(int) * heap->n * 1.25);

        // Returns 0 if it is not possible
        if (!allocResult) {
            return 0;
        }

        heap->info = allocResult;
    }
    // Inserts element in the last position.
    heap->n++;
    heap->info[heap->n] = elem;

    // Fix the heap.
    fixUp(heap, heap->n);

    return 1;
}

/**
 * Removes an element from the heap, according to its value.
 *
 * It searches for the first occurrence of the element and deletes
 * If there is more than one node with the same info, it removes the
 * one with smaller index. If there is no occurrence, returns the list as-is.
 * If the heap is less than 25% occupied, it reduces it by half.
 *
 * @param heap: A pointer to the heap.
 * @param elem: The value to be removed.
 * @return an int representing the success of the memory allocation.
 * It returns 0 in case of error and 1 in case of success.
 */
int removeHeap(MaxHeap *heap, int elem) {
    int i, n, aux, *allocResult;

    // Searches for the element to be deleted.
    n = heap->n;
    i = 1;
    while (i <= n && heap->info[i] != elem) {
        i++;
    }

    // If it was found.
    if (i <= n) {
        // Swaps element with the last one.
        aux = heap->info[i];
        heap->info[i] = heap->info[n];
        heap->info[n] = aux;

        // Updates counter.
        heap->n--;

        // Fix the heap.
        fixDown(heap, i);

        // Reallocates memory for the array of elements, if necessary.
        if (heap->n < heap->size * 0.25) {
            allocResult = (int *) realloc(heap->info, heap->size * 0.5);

            if (!allocResult) {
                return 0;
            }

            allocResult = heap->info;
        }
    }

    return 1;
}

/******************************************************
 ***************** OUTPUT *****************************
 ******************************************************/
/**
 * Prints a representation of the heap.
 *
 * It prints the elements in the order they appear in the
 * storage array.
 *
 * @param heap: The heap to be printed.
 */
void print(MaxHeap heap) {
    int i, n;

    n = heap.n;
    for (i = 1; i <= n; i++) {
        printf("%d ", heap.info[i]);
    }
    printf("\n");
}
