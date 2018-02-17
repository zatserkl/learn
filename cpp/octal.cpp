/*
clang++ -std=c++14 -Wall octal.cpp
*/

#include <cstdio>

// Just to make sure that the input with leading zero, e.g 09 will not be considered as octal.

int main()
{
    int number = 0;
    printf("Enter number: ");
    scanf("%2d", &number);
    printf("You entered %d\n", number);

    return 0;
}
