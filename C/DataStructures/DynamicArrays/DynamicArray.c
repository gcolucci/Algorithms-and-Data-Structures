#include <stdlib.h>
#include <stdio.h>

#include "DynamicArray.h"

/******************************************************
 ***************** MEMORY MANAGEMENT ******************
 ******************************************************/
 /**
 * Creates a new array with pre-defined initial size.
 *
 * It allocates space in the memory to store the amount of
 * elements passed by parameter. It also initializes the counter
 * of elements with 0 and its size to n.
 *
 * @param array: A pointer to the array structure to be initialized.
 * @param n: The initial size of the array.
 * @return an int representing the success of the memory allocation.
 * It returns 0 in case of error and 1 in case of success.
 */
int createArray(Array *array, int n) {
    if (!array) {
        return 0;
    }

    array->info = (int *) malloc(sizeof(int) * n);

    if (array->info) {
        array->n = 0;
        array->size = n;

        return 1;
    }

    return 0;
}

/**
 * Frees the memory used by the array.
 *
 * @param array: The array which info is to be
 * freed.
 */
void freeArray(Array *array) {
    if (array) {
        free(array->info);
    }
}

/******************************************************
 ***************** BASIC OPERATIONS *******************
 ******************************************************/
/**
 * Inserts a new element in the end of the array.
 *
 * It assumes that the array already has memory already
 * allocated and that all elements are correctly positioned
 * before the insertion. If the memory allocation must be expanded,
 * it increases it by 25%. If there is not enough memory for such
 * expansion, it does not verify if it is possible to expand it less.
 *
 * @param array: A pointer to the array.
 * @param elem: The new value to be inserted.
 * @return an int representing the success of the memory allocation.
 * It returns 0 in case of error and 1 in case of success.
 */
int insertArray(Array *array, int elem) {
    int n, *allocResult;

    return insertArrayAt(array, elem, array->n);
}

/**
 * Inserts a new element in a specific position of the array.
 *
 * It assumes that the array already has memory already
 * allocated and that all elements are correctly positioned
 * before the insertion. If the memory allocation must be expanded,
 * it increases it by 25%. If there is not enough memory for such
 * expansion, it does not verify if it is possible to expand it less.
 *
 * The position can be anything in the range between 0 and n. It does 
 * not allow the creation of empty spaces between elements.
 *
 * @param array: A pointer to the array.
 * @param elem: The new value to be inserted.
 * @param pos: The position to insert the new value.
 * @return an int representing the success of the memory allocation.
 * It returns 0 in case of error and 1 in case of success.
 */
int insertArrayAt(Array *array, int elem, int pos) {
    int i, *allocResult;

    int n = array->n;
    if (!array || pos < 0 || pos > n) {
        return 0;
    }

    // If the array can't fit more elements.
    if (n == array->size) {
        // Reallocates the memory for the elements array.
        allocResult = (int *) realloc(array->info, sizeof(int) * n * 1.25);

        // Returns 0 if it is not possible.
        if (!allocResult) {
            return 0;
        }

        array->info = allocResult;
        array->size *= 1.25;
    }

    // Moves to the right all elements from pos on.
    for (i = n; i > pos; i--) {
        array->info[i] = array->info[i-1];
    }

    // Inserts element in the specified position.
    array->info[pos] = elem;
    array->n++;

    return 1;
}

/**
 * Removes an element from the array, according to its value.
 *
 * It searches for the first occurrence of the element and deletes
 * If there is more than one node with the same info, it removes the
 * one with smaller index. If there is no occurrence, returns the list as-is.
 * If the array is less than 25% occupied, it reduces it by half.
 *
 * The removal changes the order of the elements - the last
 * element is placed in the position of the element to be deleted.
 *
 * @param array: A pointer to the array.
 * @param elem: The value to be removed.
 * @return an int representing the success of the memory allocation.
 * It returns 0 in case of error and 1 in case of success.
 */
int removeArray(Array *array, int elem) {
    int i, n, aux, *allocResult;

    if (!array) {
        return 0;
    }

    // Searches for the element to be deleted.
    n = array->n;
    i = 0;
    while (i < n && array->info[i] != elem) {
        i++;
    }

    // If it was found.
    if (i < n) {
        return removeArrayAt(array, i);
    }

    return 1;
}

/**
 * Removes an element from the array, according to its value.
 *
 * It searches for the first occurrence of the element and deletes
 * If there is more than one node with the same info, it removes the
 * one with smaller index. If there is no occurrence, returns the list as-is.
 * If the array is less than 25% occupied, it reduces it by half.
 *
 * The removal is stable, i.e., elements remain in their relative order.
 *
 * @param array: A pointer to the array.
 * @param elem: The value to be removed.
 * @return an int representing the success of the memory allocation.
 * It returns 0 in case of error and 1 in case of success.
 */
int removeArrayStable(Array *array, int elem) {
    int i, j, n, aux, *allocResult;

    if (!array) {
        return 0;
    }

    // Searches for the element to be deleted.
    n = array->n;
    i = 0;
    while (i < n && array->info[i] != elem) {
        i++;
    }

    // If it was found.
    if (i < n) {
        return removeArrayAtStable(array, array->n-1);
    }

    return 1;
}

/**
 * Removes an element from a specific position of the array.
 *
 * It searches for the first occurrence of the element and deletes
 * If there is more than one node with the same info, it removes the
 * one with smaller index. If there is no occurrence, returns the list as-is.
 * If the array is less than 25% occupied, it reduces it by half.
 *
 * The removal changes the order of the elements - the last
 * element is placed in the position of the element to be deleted.
 *
 * @param array: A pointer to the array.
 * @param pos: The position where to remove the value.
 * @return an int representing the success of the memory allocation.
 * It returns 0 in case of error and 1 in case of success.
 */
int removeArrayAt(Array *array, int pos) {
    int i, n, aux, *allocResult;

    if (!array || pos < 0 || pos >= array->n) {
        return 0;
    }

    // Updates counter.
    array->n--;
    n = array->n;

    // Swaps element with the last one.
    aux = array->info[pos];
    array->info[pos] = array->info[n];
    array->info[n] = aux;

    // Reallocates memory for the array of elements, if necessary.
    if (n < array->size * 0.25) {
        allocResult = (int *) realloc(array->info, sizeof(int) * array->size * 0.5 + 1);

        if (!allocResult) {
            return 0;
        }

        array->info = allocResult;
        array->size *= 0.5;
    }

    return 1;
}

/**
 * Removes an element from a specific position of the array.
 *
 * It searches for the first occurrence of the element and deletes
 * If there is more than one node with the same info, it removes the
 * one with smaller index. If there is no occurrence, returns the list as-is.
 * If the array is less than 25% occupied, it reduces it by half.
 *
 * The removal is stable, i.e., elements remain in their relative order.
 *
 * @param array: A pointer to the array.
 * @param pos: The position where to remove the value.
 * @return an int representing the success of the memory allocation.
 * It returns 0 in case of error and 1 in case of success.
 */
int removeArrayAtStable(Array *array, int pos) {
    int i, n, aux, *allocResult;

    n = array->n;
    if (!array || pos < 0 || pos >= n) {
        return 0;
    }

    // Moves to the left all elements after the one to be removed.
    for (i = pos; i < n-1; i++) {
        array->info[i] = array->info[i+1];
    }

    // Updates counter.
    array->n--;

    // Reallocates memory for the array of elements, if necessary.
    if (array->n < array->size * 0.25) {
        allocResult = (int *) realloc(array->info, sizeof(int) * array->size * 0.5 + 1);

        if (!allocResult) {
            return 0;
        }

        array->info = allocResult;
        array->size *= 0.5;
    }

    return 1;
}

/**
 * Swaps two elements in the array.
 *
 * It assumes that the indexes passed as parameters are within the
 * array bounds.
 *
 * @param array: A pointer to the array.
 * @param i: The position of the first element.
 * @param j: The position of the second element.
 */
void swapElements(Array *array, int i, int j) {
    int aux;

    aux = array->info[i];
    arra->info[i] = array->info[j];
    array->info[j] = aux;
}

/******************************************************
 ***************** OUTPUT *****************************
 ******************************************************/
/**
 * Prints a representation of the array.
 *
 * It prints the elements in the order they appear in the
 * storage array.
 *
 * @param array: The array to be printed.
 */
void print(Array array) {
    int i, n;

    n = array.n;
    printf("size = %d e n = %d | ", array.size, array.n);
    for (i = 0; i < n; i++) {
        printf("%d ", array.info[i]);
    }
    printf("\n");
}
