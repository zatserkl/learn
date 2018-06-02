/*
clang++ -Wall -std=c++17 running_median.cpp
*/

#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

using std::cout;    using std::endl;

class MedianFinder {
    friend std::ostream& operator <<(std::ostream& os, const MedianFinder& medianFinder)
    {
        // NB: queue is NOT a container but a container ADAPTER, therefore
        // there are no operators begin and end in std::queue,
        // to print the content of the queue make a copy and pop out of copy
        
        std::priority_queue lo_copy(medianFinder.lo);
        std::priority_queue hi_copy(medianFinder.hi);

        os << "lo:";
        while (!lo_copy.empty())
        {
            os << " " << lo_copy.top();
            lo_copy.pop();
        }

        os << " hi:";
        while (!hi_copy.empty())
        {
            os << " " << hi_copy.top();
            hi_copy.pop();
        }
        return os;
    }

    // lo: the left part of the sequence, the top is the max element
    // hi: the right part of the sequence, the top is the min element

    std::priority_queue<int> lo;                                        // left part, top: max element
    std::priority_queue<int, std::vector<int>, std::greater<int>> hi;   // right part, top: min element

public:
    void addNum(int num) {
        // Adds a number into the data structure.
        // To get the median use in findMedian():
        // return lo.size() > hi.size() ? (double) lo.top() : (lo.top() + hi.top()) * 0.5;

        lo.push(num);                   // Add to the lower part of the sequence

        hi.push(lo.top());              // balancing step: move max element to the right part
        lo.pop();

        if (lo.size() < hi.size()) {    // maintain size property: lo.size() >= hi.size()
            lo.push(hi.top());          // move the min element of the right part into the left part
            hi.pop();
        }
    }

    void addNum_inverse(int num) {
        // Adds a number into the data structure.
        // To get the median use in findMedian():
        // return hi.size() > lo.size() ? (double) hi.top() : (lo.top() + hi.top()) * 0.5;

        hi.push(num);                   // add to the higher part of the sequence

        lo.push(hi.top());              // balancing step: move min element to the left part
        hi.pop();

        if (hi.size() < lo.size()) {    // maintain size property: hi.size() >= lo.size()
            hi.push(lo.top());          // move the min element of the right part into the left part
            lo.pop();
        }
    }

    double findMedian() {
        // Returns the median of current data stream

        // NB: lo.size() >= hi.size()
        return lo.size() > hi.size() ? (double) lo.top() : (lo.top() + hi.top()) * 0.5;

        // // NB: hi.size() >= lo.size(): to serve addNum_inverse
        // return hi.size() > lo.size() ? (double) hi.top() : (lo.top() + hi.top()) * 0.5;
    }
};

int main()
{
    MedianFinder* obj = new MedianFinder();

    obj->addNum(4);
    obj->addNum(5);
    double param_2 = 0;

    param_2 = obj->findMedian();
    cout<< std::setw(8) << param_2 << " num: " << *obj <<endl;

    obj->addNum(15);
    param_2 = obj->findMedian();
    cout<< std::setw(8) << param_2 << " num: " << *obj <<endl;

    obj->addNum(1);
    param_2 = obj->findMedian();
    cout<< std::setw(8) << param_2 << " num: " << *obj <<endl;

    obj->addNum(3);
    param_2 = obj->findMedian();
    cout<< std::setw(8) << param_2 << " num: " << *obj <<endl;
}
