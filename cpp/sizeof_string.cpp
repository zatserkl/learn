#include <iostream>
#include <string>

using std::cout;    using std::endl;

int main()
{
    std::string dictionary[] = {"mobile","samsung","sam","sung",
        "man","mango","icecream","and",
        "go","i","like","ice","cream"};
    int size = sizeof(dictionary)/sizeof(dictionary[0]);
    cout<< "sizeof(dictionary) = " << sizeof(dictionary) <<endl;
    cout<< "sizeof(dictionary[0]) = " << sizeof(dictionary[0]) <<endl;
    cout<< "size = " << size <<endl;

    std::string str50 = "123456789 123456789 123456789 123456789 1234567890";
    cout<< str50 <<endl;
    cout<< "sizeof(str50) = " << sizeof(str50) <<endl;

    return 0;
}
