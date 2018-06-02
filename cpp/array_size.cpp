#include <iostream>
#include <string>

using std::cout;      using std::endl;

void array_size(const std::string array[]) {
    cout<< sizeof(*array) <<endl;   // returns sizeof(std::string)
}

int main()
{
    std::string array[] = {"one", "two", "three", "four", "five"};

    cout<< "sizeof(array) / sizeof(std::string) = "
        << sizeof(array) << " / " << sizeof(std::string) << " = "
        << sizeof(array) / sizeof(std::string) <<endl;

    array_size(array);      // prints the number of elements in the array
}
