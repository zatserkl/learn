/*
clang++ -Wall -std=c++17 hello_multithead.cpp
*/

#include <iostream>
#include <thread>

void hello()
{
    long n = 0;
    n = 1000000;   // if detached and n = 1000000 will be no printout
    long sum = 0;
    for (int i=0; i<n; ++i) {
        sum++;
    }

    // std::cout<< "Hello Concurrent World!" <<std::endl;
    std::cout<< "Hello Concurrent World!\n";
}

int main()                  // main in fact is an initial thread
{
    std::thread t(hello);   // call constructor with initial function hello()
    std::cout<< "main: continue after launching the thread hello\n";

    std::cout<< "before t.detach(): t.joinable() = " << t.joinable() << "\n";
    // t.join();    // after t.join() t.joinable() will be false

    if (t.joinable()) {
        std::cout<< "t is joinable, detach it\n";
        t.detach();     // if detached and n = 1000000 will be no printout
        std::cout<< "after t.detach(): t.joinable() = " << t.joinable() << "\n";
    }
    else {
        std::cout<< "t is NOT joinable, cannot detach it\n";
    }

    return 0;
}
