// http://www.cplusplus.com/reference/functional/ref/

/*
need -std=c++11 because of auto:

clang++ -Wall -std=c++11 ref_example.cpp
*/

// ref example
#include <iostream>     // std::cout
#include <functional>   // std::ref

int main () {
    int foo(10);        // define int foo and initialize it with 10

    auto bar = std::ref(foo);

    ++bar;

    std::cout << foo << '\n';

    return 0;
}
