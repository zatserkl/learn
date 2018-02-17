// from https://www.youtube.com/watch?v=U0nvXHh7o-w

/*
cc -Wall dynamic_prog_maxsum.c
./a.out 10 101 120
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

//
// The macros MIN and MAX can be defined like followed, but
// it's better to awoid them thatsoever. E.g. they break up for MAX(++a, ++b)
//
// #define MAX(x, y) (((x) > (y)) ? (x) : (y))
// #define MIN(x, y) (((x) < (y)) ? (x) : (y))

int maximal_subarray_space_draft(int *array, int n)
{
    // build out solution array
    int *subproblem = (int *) malloc(n * sizeof(int));

    //--do_not_use_macro_MAX-- subproblem[0] = MAX(array[0], 0);
    subproblem[0] = array[0] > 0? array[0]: 0;
    for (int i=1; i<n; ++i) {
        //--do_not_use_macro_MAX-- subproblem[i] = MAX(subproblem[i-1] + array[i], 0); // NB: put 0 for negative sum
        int curr = subproblem[i-1] + array[i];
        subproblem[i] = curr > 0? curr: 0;  // NB: put 0 for negative sum
    }

    // iterate through to find the solution
    int max = 0;
    for (int i=0; i<n; ++i) {
        //--do_not_use_macro_MAX-- max = MAX(max, subproblem[i]);
        max = subproblem[i] > max? subproblem[i]: max;
    }

    free(subproblem);
    return max;
}

int maximal_subarray_space(int *array, int n)
{
    int sum_curr = 0;
    int max_curr = 0;

    for (int i=0; i<n; ++i) {
        sum_curr = sum_curr + array[i] > 0? sum_curr + array[i]: 0;
        if (sum_curr > max_curr) max_curr = sum_curr;
    }

    return max_curr;
}

int main(int argc, char* argv[])
{
    int n = 10;
    int min = -10;
    int max = +10;

    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) min = atoi(argv[2]);
    if (argc > 3) max = atoi(argv[3]);

    printf("n = %d elements, min = %d, max = %d\n", n, min, max);

    int *array = (int *) malloc(n * sizeof(int));

    srand(100);
    for (int i=0; i<n; ++i) {
        array[i] = rand() % (max - min) + min;
    }

    for (int i=0; i<n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    int maxsum = maximal_subarray_space(array, n);

    printf("maximal_subarray_space = %d\n", maxsum);

    return 0;
}
