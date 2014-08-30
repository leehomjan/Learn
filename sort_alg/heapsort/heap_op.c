#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) \
        do { typeof(*a) __tmp = (*a); (*a) = (*b); (*b) = __tmp; } while (0)

#define MAX_HEAP 1
#define MIN_HEAP 2

static const int HEAP_MAX_SIZE = 100;
static int heap[HEAP_MAX_SIZE];
static int heap_size = 0;

static void(*shift_up)(int) = NULL;
static void(*shift_down)(int) = NULL;

static void maxheap_shift_up(int idx)
{
    int done = 0;
    if (idx == 0) return; // root
    while (idx!=0 && !done) {
        if (heap[(idx-1)/2] < heap[idx]) {
            swap(&heap[(idx-1)/2], &heap[idx]);
        } else {
            done = 1;
        }
        idx = (idx -1)/2;
    }
}

static void maxheap_shift_down(int idx)
{
    int done = 0;
    if (2*idx+1 >= heap_size) return; // leaf
    while (2*idx+1 < heap_size && !done) {
        idx = 2*idx+1;
        if (idx+1<heap_size && heap[idx+1] > heap[idx]) {
            //right child is greater than left
            ++idx;
        }
        if (heap[(idx-1)/2] < heap[idx]) {
            swap(&heap[(idx-1)/2], &heap[idx]);
        } else {
            done = 1;
        }
    }
}

static void minheap_shift_up(int idx)
{
    int done = 0;
    if (idx == 0) return; // root
    while (idx!=0 && !done) {
        if (heap[(idx-1)/2] > heap[idx]) {
            swap(&heap[(idx-1)/2], &heap[idx]);
        } else {
            done = 1;
        }
        idx = (idx -1)/2;
    }
}

static void minheap_shift_down(int idx)
{
    int done = 0;
    if (2*idx+1 >= heap_size) return; // leaf
    while (2*idx+1 < heap_size && !done) {
        idx = 2*idx+1;
        if (idx+1<heap_size && heap[idx+1] < heap[idx]) {
            //right child is greater than left
            ++idx;
        }
        if (heap[(idx-1)/2] > heap[idx]) {
            swap(&heap[(idx-1)/2], &heap[idx]);
        } else {
            done = 1;
        }
    }
}

void delete(int idx)
{
    int last = heap[heap_size-1];
    --heap_size;
    if (idx == heap_size) return; // delete last one
    heap[idx] = last;
    shift_down(idx);
}

int delete_top()
{
    int ret = heap[0];
    delete(0);
    return ret;
}

void insert(int data)
{
    if (heap_size >= HEAP_MAX_SIZE) return;
    ++heap_size;
    heap[heap_size-1] = data;
    shift_up(heap_size-1);
}

void heap_init(int heap_type)
{
    if (heap_type == MAX_HEAP) {
        shift_up = maxheap_shift_up;
        shift_down = maxheap_shift_down;
    } else {
        shift_up = minheap_shift_up;
        shift_down = minheap_shift_down;
    }
}

void do_print()
{
    int idx = 0;
    while (idx<heap_size) {
        printf("%d ", heap[idx]);
        ++idx;
    }
    printf("\n");
}

int main()
{
    heap_init(MAX_HEAP);
    insert(3);
    insert(5);
    insert(6);
    insert(4);
    insert(1);
    insert(2);
    insert(8);
    insert(7);
    do_print();
    
    return 0;
}
