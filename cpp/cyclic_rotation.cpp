// Andriy Zatserklyaniy <zatserkl@gmail.com> Oct 14, 2018

// https://app.codility.com/programmers/lessons/2-arrays/cyclic_rotation/

/*
clang++ -Wall -std=c++17 cyclic_rotation.cpp
*/

#include <iostream>
#include <vector>

using std::cout;    using std::endl;

std::vector<int> cyclic_rotation(const std::vector<int>& A, int K)
{
    // rotate vector A K times
    // NB: for K = A.size() the vector stays the same. I don't use that.

    std::vector<int> vout(A.size());

    for (int i=0; i<A.size(); ++i)
    {
        vout[(i + K) % A.size()] = A[i];
    }

    return vout;
}

int main()
{
    // std::vector<int> A{1, 2, 3};
    // int K = 2;

    std::vector<int> A{1, 2, 3, 4};
    int K = 4;

    auto vout = cyclic_rotation(A, K);
    for (auto x: vout) cout<< x << ' ';
    cout<<endl;
}
