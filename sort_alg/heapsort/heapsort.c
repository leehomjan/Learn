/*
 * Create at 2014/08/30 by leehomjan
 */
#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) \
        do { typeof(*a) __tmp = (*a); (*a) = (*b); (*b) = __tmp; } while (0)

static void shift_up(int* heap, int idx, int(*cmp)(int,int))
{
    int done = 0;
    if (idx == 0) return; // root
    while (idx!=0 && !done) {
        if (cmp(heap[(idx-1)/2], heap[idx]) > 0) {
            swap(&heap[(idx-1)/2], &heap[idx]);
        } else {
            done = 1;
        }
        idx = (idx -1)/2;
    }
}

static void shift_down(int* heap, int idx, int heap_size, int(*cmp)(int, int))
{
    int done = 0;
    if (2*idx+1 >= heap_size) return; // leaf
    while (2*idx+1 < heap_size && !done) {
        idx = 2*idx+1;
        if (idx+1<heap_size && cmp(heap[idx+1], heap[idx])<0) {
            //right child is greater than left
            ++idx;
        }
        if (cmp(heap[(idx-1)/2], heap[idx])>0) {
            swap(&heap[(idx-1)/2], &heap[idx]);
        } else {
            done = 1;
        }
    }
}

static void delete(int* heap, int idx, int* heap_size, int(*cmp)(int ,int))
{
    int last = heap[*heap_size-1];
    --(*heap_size);
    if (idx == *heap_size) return; // delete last one
    heap[idx] = last;
    shift_down(heap, idx, *heap_size, cmp);
}

static int delete_top(int* heap, int* heap_size, int(*cmp)(int,int))
{
    int ret = heap[0];
    delete(heap, 0, heap_size, cmp);
    return ret;
}

static void insert(int data, int* heap, int* heap_size, int(*cmp)(int,int))
{
    ++(*heap_size);
    heap[*heap_size-1] = data;
    shift_up(heap, *heap_size-1, cmp);
}

static void do_print(int* base, int sz)
{
    int idx = 0;
    while (idx<sz) {
        printf("%d ", base[idx]);
        ++idx;
    }
    printf("\n");
}

void heap_sort(int* base, int sz, int(*cmp)(int, int))
{
    int heap_size = 1;

    if (sz <= 1) return;

    //  create heap
    while (heap_size < sz) {
        insert(base[heap_size], base, &heap_size, cmp);
    }

    do_print(base, sz);
    // do sort
    while (heap_size > 0) {
        int top = delete_top(base, &heap_size, cmp);
        base[heap_size] = top;
    }
    do_print(base, sz);
}

static inline int maxheap_cmp(int a, int b)
{
    if (a == b) return 0;
    if (a < b) return -1;
    else return 1;
}

static inline int minheap_cmp(int a, int b)
{
    if (a == b) return 0;
    if (a > b) return -1;
    else return 1;
}

int main()
{
    int a[] ={3, 5, 6, 4, 1, 2, 8, 7};
    int sz = 8;
    do_print(a, sz);

    heap_sort(a, sz, minheap_cmp);
    
    return 0;
}
