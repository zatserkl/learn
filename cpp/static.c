/*
from http://stackoverflow.com/questions/572547/what-does-static-mean-in-a-c-program

A static variable inside a function keeps its value between invocations.
A static global variable or a function is "seen" only in the file it's declared in

gcc static.c
*/

#include <stdio.h>

void foo()
{
    int a = 10;
    static int sa = 10;

    a += 5;
    sa += 5;

    printf("a = %d, sa = %d\n", a, sa);
}


int main()
{
    int i;

    for (i = 0; i < 10; ++i)
        foo();
}
