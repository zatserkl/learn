// https://solarianprogrammer.com/2017/05/21/compiling-gcc-macos/

// Program to test the C++ lambda syntax and initializer lists

/*
clang++ -Wall -std=c++14 lambda.cpp
*/

#include <iostream>
#include <vector>

using std::cout;    using std::endl;

int main()
{
    // Test lambda
    cout << [](int m, int n) {return m + n;} (2,4) << endl;

    // Test initializer lists and range based for loop
    std::vector<int> V({1,2,3});

    cout << "Content of V:" << endl;
    for(auto e : V) {
        cout << e << endl;
    }
}
