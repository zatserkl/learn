/*
clang++ -Wall -std=c++14 auto.cpp
*/

#include <vector>
#include <algorithm>
#include <iostream>

using std::cout;      using std::endl;

int main()
{
    int array[] = {10, 20, 30, 40};

    std::vector<int> vec(array, array+sizeof(array)/sizeof(int));

    cout<< "Original array:" <<endl;
    for (auto const& x: vec) cout<< x << endl;

    cout<< "Unsuccessful attempt to change array using auto x:" <<endl;
    for (auto x: vec) x *= 100;
    for (auto const& x: vec) cout<< x << endl;

    //
    //  This piece will not be compiled: error: cannot assign to variable 'x' with const-qualified type 'const int &'
    //
    // cout<< "Unsuccessful attempt to change array using more effective (avoid copying) const auto& x:" <<endl;
    // for (const auto& x: vec) x *= 100;

    cout<< "Successful attempt to change array using auto& x:" <<endl;
    for (auto& x: vec) x *= 100;
    for (auto const& x: vec) cout<< x << endl;

    cout<< "Restore original array and efficiently reference to elements (w/o copying) with const auto& x" <<endl;
    std::copy(array, array+sizeof(array)/sizeof(int), vec.begin());

    for (auto const& x: vec) cout<< x << endl;

    return 0;
}
