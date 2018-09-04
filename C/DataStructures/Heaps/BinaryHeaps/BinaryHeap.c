#include <stdlib.h>
#include <stdio.h>

#include "Heap.h"

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
int createHeap(Heap *heap, int n) {
    if (!heap) {
        return 0;
    }

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
void freeHeap(Heap *heap) {
    if (heap) {
        free(heap->info);
    }
}

/******************************************************
 ***************** BASIC OPERATIONS *******************
 ******************************************************/
/**
 * Extracts the top element of the heap.
 *
 * It returns the top element of the heap and removes it from the
 * structure. If the heap is less than 25% occupied, it reduces it by half.
 *
 * The top element represents the minimum or the maximum value
 * stored, depending on the heap type. Its value is stored in the first
 * pointer, received by parameter. If any error occurs, first is not
 * changed.
 *
 * @param heap: A pointer to the heap.
 * @param first: A pointer to store the top element value.
 * @return 1 if successful, 0 otherwise.
 */
int extractHeap(Heap *heap, int *top) {
    int n, temp, *allocResult;

    if (!heap) {
        return 0;
    }

    n = heap->n;

    // If heap is empty.
    if (n == 0) {
        return 0;
    }

    // Gets first element.
    temp = heap->info[1];

    // Puts last element in the first position.
    heap->info[1] = heap->info[n];

    // Fix the heap.
    heap->n--;
    fixDown(heap, 1);

    if (heap->n < heap->size * 0.25) {
        allocResult = (int *) realloc(heap->info, sizeof(int) * heap->size * 0.5 + 1);

        if (!allocResult) {
            return 0;
        }

        heap->info = allocResult;
        heap->size *= 0.5;
    }

    *top = temp;

    return 1;
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
int insertHeap(Heap *heap, int elem) {
    int *allocResult;

    if (!heap) {
        return 0;
    }

    // If the heap can't fit more elements
    if (heap->n == heap->size) {
        // Reallocates the memory for the elements array.
        allocResult = (int *) realloc(heap->info, sizeof(int) * heap->n * 1.25);

        // Returns 0 if it is not possible
        if (!allocResult) {
            return 0;
        }

        heap->info = allocResult;
        heap->size *= 1.25;
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
int removeHeap(Heap *heap, int elem) {
    int i, n, aux, *allocResult;

    if (!heap) {
        return 0;
    }

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
            allocResult = (int *) realloc(heap->info, sizeof(int) * heap->size * 0.5 + 1);

            if (!allocResult) {
                return 0;
            }

            heap->info = allocResult;
            heap->size *= 0.5;
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
void print(Heap heap) {
    int i, n;

    n = heap.n;
    for (i = 1; i <= n; i++) {
        printf("%d ", heap.info[i]);
    }
    printf("\n");
}
