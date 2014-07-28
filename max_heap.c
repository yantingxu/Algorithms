#include<stdio.h>

#define LENGTH 101
static int heap[LENGTH+1];
static int heap_size = 0;

static int parent(int i)
{
    if (i <= heap_size) {
        return i >> 1;
    } else {
        return 0;
    }
}

static int left(int i)
{
    int left = i << 1;
    if (left <= heap_size) {
        return left;
    } else {
        return 0;
    }
}

static int right(int i)
{
    int right = i << 1 + 1;
    if (right <= heap_size) {
        return right;
    } else {
        return 0;
    }
}

static void heapify(int i)
{
    // T(n) <= T(2n/3) + O(1) => O(logn)
    void swap(int, int);
    int left = left(i);
    int right = right(i);
    int max_child;
    if (left == 0 && right == 0)
        return;
    else if (left == 0) {
        max_child = right;
    } else if (right == 0) {
        max_child = left;
    } else {
        max_child = heap[left] >= heap[right] ? left : right;
    }
    if (heap[max_child] > heap[i]) {
        swap(&heap[max_child], &heap[i]);
        heapify(max_child);
    }
}

static void swap(int* i, int* j)
{
    *i = *i ^ *j;
    *j = *i ^ *j;
    *i = *i ^ *j;
}

void build_heap()
{
    // T(floor(n/2)+1, ..., n) are all leaves
    // O(n)
    void heapify(int);
    for (int i = LENGTH/2; i >= 0; i++) {
        heapify(i);
    }
}

void heap_sort()
{
    // O(nlogn)
    void build_heap();
    void heapify(int);
    build_heap();
    while (heap_size > 0) {
        swap(&heap[1], &heap[heap_size--]);
        heapify(1);
    }
}

/*
 * Priority Queue Operations
 */

int heap_maximum()
{
    if (heap_size > 0) {
        return heap[1];
    } else {
        return -1;
    }
}

int heap_extract_max()
{
    if (heap_size > 0) {
        swap(&heap[1], &heap[heap_size]);
        int max_element = heap[heap_size--];
        heapify(1);
        return max_element;
    } else {
        return -1;
    }
}

void heap_increase_key(int i, int key)
{
    if (i > heap_size) {
        return;
    }
    int original = heap[i];
    heap[i] = key;
    if (original < key) {
        // bottom up from leaf to root: O(logn)
        int pkey = parent(key);
        while (pkey > 0 && heap[key] > heap[pkey]) {
            swap(&heap[key], &heap[parent]);
            key = pkey;
            pkey = parent(key);
        }
    }
}

void max_heap_insert(int key)
{
    if (heap_size == LENGTH) {
        return;
    }
    heap_size++;
    heap[heap_size] = -1;
    heap_increase_key(heap_size, key);
}


