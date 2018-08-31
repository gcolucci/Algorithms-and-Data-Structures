typedef struct heap {
    // Defines a heap of ints. n will store the
    // number of elements in the heap and size
    // the number of elements allocated in the
    // memory.
    int *info, n, size;
} Heap;

int createHeap(Heap *heap, int n);
void freeHeap(Heap *heap);
void fixUp(Heap *heap, int k);
void fixDown(Heap *heap, int k);
int extractHeap(Heap *heap);
int insertHeap(Heap *heap, int elem);
int removeHeap(Heap *heap, int elem);
void print(Heap heap);
