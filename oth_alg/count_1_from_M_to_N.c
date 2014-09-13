/*
 * Create at 2014/09/13 By leehomjan
 */
#include <stdio.h>
#include <stdlib.h>

static int count(int orig)
{
    int div = 1; // divisor
    int count = 0;

    int quo = 0; // quotient
    int curr = 0; // current bit
    int rem = 0; // remainder
    // count 1s in bit ten hundred ...
    while (orig / div) {
<<<<<<< HEAD
        rem = orig%div;
=======
        rem = orig％div;
>>>>>>> FETCH_HEAD
        quo = orig/(div*10);
        curr = (orig/div)%10;

        switch (curr) {
            case 0:
                // orig=20200 div=1000
                // there has 2000 1s in thousand bit
                // they are 01[000...999] and 11[000...999]
                count += quo*div;
                break;
            case 1:
                // orig=20165 div=100
                // there has 2066 1s in hundred bit
                // they are [00...19]1[00...99] + 201[00...65]
                count += quo*div + (rem+1);
                break;
            default:
                // orig=20200 div=100
                // there has 2100 1s in hundred bit
                // they are [00...20]1[00...99]
                count += (quo+1)*div;
        }
        printf("%d\n", count);
        div *= 10;
    }
    return count;
}


static inline int get_count(int from, int to)
{ 
    return count(to) - count(from);
}

int main(int argc, char* argv[])
{
    int from = 0;
    int to = 0;
    int rst = 0;

    if (argc == 1 || argc > 3) {
        printf("./count_1_from_M_to_N {<M> <N>|<N>}\n");
        return 1;
    }

    if (argc == 2) {
        to = atoi(argv[1]);
    } else {
        from = atoi(argv[1]);
        to = atoi(argv[2]);
    }
    rst = get_count(from, to);

    printf("There has %d 1s from %d to %d\n", rst, from, to);

    return 0;
}
