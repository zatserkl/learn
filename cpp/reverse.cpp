// Andriy Zatserklyaniy <zatserkl@gmail.com> Oct 14, 2018

/*
clang++ -Wall -std=c++17 reverse.cpp
*/

#include <iostream>

using std::cout;    using std::endl;

void reverse(int A[], int N)
{
    for (int i=0; i<N/2; ++i)
    {
        int k = N - i - 1;
        int tmp = A[i];
        A[i] = A[k];
        A[k] = tmp;
    }
}

int main()
{
    int A[] = {1, 2, 3, 4};
    int N = sizeof(A) / sizeof(N);

    reverse(A, N);

    for (auto a: A) cout<< a << ' ';
    cout<<endl;
}
