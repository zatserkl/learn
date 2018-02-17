#include <iostream>

using std::cout;      using std::endl;

void fun(int* ptr) {
    if (ptr != nullptr) cout << *ptr <<endl;
    else cout<< "nullptr" <<endl;
}

int main()
{
    int* ptr = nullptr;
    fun(ptr);

    return 0;
}
