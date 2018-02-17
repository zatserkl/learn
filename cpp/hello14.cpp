/*
clang++ -std=c++14 hello14.cpp
// g++ -std=c++1y hello14.cpp
*/

#include <iostream>
#include <string>

int main(void)
{
    //-- using namespace std::string_literals;
    using std::operator ""s;

    auto output = "Hello World! \0 I really meant Hello!"s; // ""s ignores \0 in the string
    std::cout << output << std::endl;

    return 0;
}
