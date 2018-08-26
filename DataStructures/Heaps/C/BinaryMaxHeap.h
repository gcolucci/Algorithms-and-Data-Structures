typedef struct maxHeap {
    // Defines a heap of ints. n will store the
    // number of elements in the heap and size
    // the number of elements allocated in the
    // memory.
    int *info, n, size;
} MaxHeap;

int createHeap(MaxHeap *heap, int n);
void freeHeap(MaxHeap *heap);
void fixUp(MaxHeap *heap, int k);
void fixDown(MaxHeap *heap, int k);
int extractMax(MaxHeap *heap);
int insertHeap(MaxHeap *heap, int elem);
int removeHeap(MaxHeap *heap, int elem);
void print(MaxHeap heap);
