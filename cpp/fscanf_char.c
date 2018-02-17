#include <stdio.h>

int main()
{
    FILE *f = fopen(__FILE__, "r");

    char c;
    while (fscanf(f, "%c", &c) != EOF) printf("%c",c);

    return 0;
}
