#include <stdlib.h>
#include <stdio.h>

#include "Heap.h"

/******************************************************
 ***************** FIX OPERATIONS *********************
 ******************************************************/
/**
 * Fix the position of misplaced nodes in the path from the
 * k-th element to the heap root.
 *
 * Fixing the heap means to rearrange the elements so every
 * node in the path is lesser or equal to all of its
 * descendants. It traverses the heap bottom-up and stops
 * when the first element in the correct position is found.
 * It assumes the heap was fixed after all updates, so
 * it is not necessary to check the whole path.
 *
 * @param heap: A pointer to the heap.
 * @param k: The index of the last element to be rearranged.
 */
void fixUp(Heap *heap, int k) {
    int aux;

    if (heap) {
        // Traverses the path
        while (k > 1 && heap->info[k] < heap->info[k/2]) {
            // Swaps elements.
            aux = heap->info[k];
            heap->info[k] = heap->info[k/2];
            heap->info[k/2] = aux;

            // Jumps to the parent.
            k /= 2;
        }
    }
}

/**
 * Fix the position of misplaced nodes in the path from the
 * k-th to its last descendant.
 *
 * Fixing the heap means to rearrange the elements so every
 * node in the path is lesser or equal to all of its
 * descendants. It traverses the heap top-down and stops
 * when the first element in the correct position is found.
 * It assumes the heap was fixed after all updates, so
 * it is not necessary to check the whole path.
 *
 * @param heap: A pointer to the heap.
 * @param k: The index of the first element to be rearranged.
 */
void fixDown(Heap *heap, int k) {
    int aux, n, i;

    if (heap) {
        n = heap->n;

        // Traverses the path.
        i = 2*k;
        while (i <= n) {
            // Chooses the lesser sibling among k children.
            if (heap->info[i] > heap->info[i+1]) {
                i = i+1;
            }

            // Stops if it found an element in the correct place.
            if (heap->info[k] <= heap->info[i]) {
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
}
