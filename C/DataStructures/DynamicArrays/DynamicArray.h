typedef struct array {
    // Defines a array of ints. n will store the
    // number of elements in the array and size
    // the number of elements allocated in the
    // memory.
    int *info, n, size;
} Array;

int createArray(Array *array, int n);
void freeArray(Array *array);
int insertArray(Array *array, int elem);
int insertArrayAt(Array *array, int elem, int pos);
int removeArray(Array *array, int elem);
int removeArrayStable(Array *array, int elem);
int removeArrayAt(Array *array, int pos);
int removeArrayAtStable(Array *array, int pos);
void swapElements(Array *array, int i, int j);
void print(Array array);
