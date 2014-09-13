/*
 * Create at 2014/09/13 By leehomjan
 */
#include <stdio.h>
#include <stdlib.h>

int find_single(int* seq, int num)
{
    int idx = 0;
    int rst = 0;

    if (num < 2) return rst;

    for (idx=0; idx<num; idx++) {
        rst ^= seq[idx];
    }
    for (idx=1; idx<=num+1; idx++) {
        rst ^= idx;
    }

    return rst;
}

int find_double(int* seq, int num, int* rst1, int* rst2)
{
    int idx = 0;
    int xy = 0;
    int x = 0;
    int y = 0;

    if (num < 3) return 1;

    for (idx=0; idx<num; idx++) {
        xy ^= seq[idx];
    }
    for (idx=1; idx<=num+2; idx++) {
        xy ^= idx;
    }

    for (idx=0; idx<32; idx++) {
        if ((xy>>idx)&0x00000001) break;
    }
    if (idx==32) return 0;

    int split = 0x00000001<<idx;

    for (idx=0; idx<num; idx++) {
        if (seq[idx]&split) {
            x ^= seq[idx];
        } else {
            y ^= seq[idx];
        }
    }
    for (idx=1; idx<=num+2; idx++) {
        if (idx&split) {
            x ^= idx;
        } else {
            y ^= idx;
        }
    }
    *rst1 = x;
    *rst2 = y;

    return 0;
}

int main()
{
    int rst = 0;
    int rst1 = 0;
    int rst2 = 0;
    int seq[] = {1,2,3,4,5,6,8,9,10};
    int seq1[] = {1,2,4,5,6,8,9,10};

    rst = find_single(seq, sizeof(seq)/sizeof(int));
    find_double(seq1, sizeof(seq1)/sizeof(int), &rst1, &rst2);

    printf("Missed number in sequence is %d\n", rst);
    printf("Missed number in sequence is %d and %d\n", rst1, rst2);

    return 0;
}
