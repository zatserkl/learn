// Andriy Zatserklyaniy <zatserkl@gmail.com> Oct 14, 2018

// see https://app.codility.com/public-report-detail/

/*
clang -Wall equilibrium_point.c
*/

#include <stdio.h>

int solution(int A[], int N)
{
    long sum_left = 0;
    long sum_right = 0;
    for (int i=1; i<N; ++i) sum_right += A[i];

    int point_first = -1;

    for (int i=0; i<N; ++i)
    {
        if (sum_left == sum_right) {
            // return i;
            if (point_first < 0) point_first = i;
            printf("current equilibrium point = %d sum = %ld\n", i, sum_left);
        }

        sum_left += A[i];
        if (i < N-1) sum_right -= A[i+1];
    }

    return point_first;
}

int main()
{
    int A1[] = {-1, 3, -4, 5, 1, -6, 2, 1};
    int nA1 = sizeof(A1) / sizeof(int);

    printf("A1:\n");
    for (int i=0; i<nA1; ++i) printf("%d\n", A1[i]);
    printf("the first equilibrium point = %d\n", solution(A1, nA1));

    printf("\n");

    int A2[] = {0, -2147483648, -2147483648};
    int nA2 = sizeof(A2) / sizeof(int);

    printf("A2:\n");
    for (int i=0; i<nA2; ++i) printf("%d\n", A2[i]);
    printf("the first equilibrium point = %d\n", solution(A2, nA2));

    printf("\n");

    int A3[] = {-2147483648, -2147483648};
    int nA3 = sizeof(A3) / sizeof(int);

    printf("A3:\n");
    for (int i=0; i<nA3; ++i) printf("%d\n", A3[i]);
    printf("the first equilibrium point = %d\n", solution(A3, nA3));

    printf("\n");

    // int nA4 = 100000;
    int nA4 = 100001;
    int A4[nA4];
    for (int i=0; i<nA4; ++i) A4[i] = 1;

    printf("A4:\n");
    printf("the first equilibrium point = %d\n", solution(A4, nA4));
}
