/*
See discussion at http://stackoverflow.com/questions/15013077/arrayn-vs-array10-initializing-array-with-variable-vs-real-number
In short: g++ extension allows

int n = 10;
int a[n];

while this is forbidden in the C++ standard (old one) without qualifier const
*/

#include <iostream>

using std::cout;      using std::endl;

void fun(int n) {
    int a[n];
    for (int i=0; i<n; ++i) a[i] = i;
    for (int i=0; i<n; ++i) cout<< a[i] <<endl;
}

int main()
{
    cout<< "call fun" <<endl;
    fun(5);

    cout<< "create local array" <<endl;
    int n = 5;
    int a[n];
    for (int i=0; i<n; ++i) a[i] = i;
    for (int i=0; i<n; ++i) cout<< a[i] <<endl;

    return 0;
}
