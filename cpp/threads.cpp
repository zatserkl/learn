// https://solarianprogrammer.com/2017/05/21/compiling-gcc-macos/

// Create a C++ thread from the main program

/*
clang++ -Wall -std=c++14 threads.cpp
*/

#include <iostream>
#include <thread>

// This function will be called from a thread
void call_from_thread() {
    std::cout << "Hello, World!" << std::endl;
}

int main() {
    //Launch a thread
    std::thread t1(call_from_thread);

    //Join the thread with the main thread
    t1.join();

    return 0;
}
