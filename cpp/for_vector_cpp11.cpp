/*
clang++ -Wall -std=c++17 for_vector.cpp
*/

#include <iostream>
#include <vector>
#include <queue>

using std::cout;      using std::endl;

int main()
{
    std::vector v{10, 20, 30, 40};  // type <int> is deduced from data

    for (auto element: v)           // element is a copy of the vector element
        cout<< element <<endl;

    std::queue<int> q;
    q.push(100);
    q.push(200);
    q.push(300);
    q.push(400);

    // queue is not a container, but a container adapter.
    //
    // there are no operators begin and end in std::queue,
    // to print the content of the queue make a copy and pop out of copy
    //
    // queue returns the max element out of all stored

    std::queue q_copy(q);

    while (!q_copy.empty()) {
        cout<< q_copy.front() <<endl;
        q_copy.pop();
    }

    return 0;
}
