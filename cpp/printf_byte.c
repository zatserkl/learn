// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format

/**
interview$ clang -Wall printf_byte.c
interview$ ./a.out 6
Use BYTE_TO_BINARY_PATTERN and BYTE_TO_BINARY(6)
76543210
00000110

Use print_binary:
110

Use bin:
110

Use bin_recursive:
call bin_recursive(6/2)
call bin_recursive(3/2)
1
3
6


Use bin_printf to print 6:
76543210
     110

Use bin_printf:
1 987654321 987654321 9876543210
                             110
bin_printf(1U << 5)
1 987654321 987654321 9876543210
                          100000
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

/**
  * for completeness: final versions of bprintf, printf_byte, and printf_int
  */
void bprintf(unsigned int n, char buf[]) // before the call set buf[0] = '\0'
{
    if (n > 1) {
        bprintf(n/2, buf);
    }

    // you are here after recursive calls
    sprintf(&buf[strlen(buf)], "%u", n%2);
}

void printf_byte(unsigned int n)
{
    // print string 76543210
    for (int i=7; i>0; --i) {
        int r = i % 10;
        if (r != 0) printf("%u", r);    // print byte number (ones only)
        else printf(" ");
    }
    printf("%u\n", 0);                  // print 0 and insert newline

    char buf[9];
    buf[0] = '\0';
    bprintf(n, buf);
    printf("%8s\n", buf);
}

void printf_int(unsigned int n)
{
    // print string 1 987654321 987654321 9876543210
    for (int i=31; i>0; --i) {
        int r = i % 10;
        if (r != 0) printf("%u", r);    // print byte number (ones only)
        else printf(" ");
    }
    printf("%u\n", 0);                  // print 0 and insert newline

    char buf[33];
    buf[0] = '\0';
    bprintf(n, buf);
    printf("%32s\n", buf);
}

// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format/25108449#25108449
void print_binary(unsigned int number)
{
    if (number) {
        print_binary(number >> 1);
        putc((number & 1) ? '1' : '0', stdout);
    }
}

void bin(unsigned int n)
{
    // part 1
    if (n > 1) {
        bin(n/2);
    }

    // part 2
    // this part will be executed after recursive call in the part 1
    printf("%u", n % 2);
}

void bin_recursive(unsigned int n)
{
    // part 1
    if (n > 1) {
        printf("call bin_recursive(%u/2)\n", n);
        bin_recursive(n/2);
    }

    // part 2
    // this part will be executed after recursive call in the part 1
    // printf("%u", n % 2);
    printf("%u\n", n);
}

//
// I moved definition of bprintf into the top of the file
//
// void bprintf(unsigned int n, char buf[])
// {
//     if (n > 1) {
//         bprintf(n/2, buf);
//     }
// 
//     // you are here after recursive calls
//     sprintf(&buf[strlen(buf)], "%u", n%2);
// }

void bin_printf(unsigned int n)
{
    for (int i=31; i>0; --i) {
        int r = i % 10;
        if (r != 0) printf("%u", r);    // print byte number (ones only)
        else printf(" ");
    }
    printf("%u\n", 0);                  // print 0 and insert newline

    char buf[33];
    buf[0] = '\0';
    bprintf(n, buf);
    printf("%32s\n", buf);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s byte\n", argv[0]);
        return 0;
    }
    unsigned char byte = (unsigned char) atoi(argv[1]);

    // unsigned char byte = 1U << 5;
    // printf("0x20:\n76543210\n"BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(byte));

    printf("Use BYTE_TO_BINARY_PATTERN and BYTE_TO_BINARY(%u)\n", byte);

    printf("76543210\n"BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(byte));

    printf("\nUse print_binary:\n");

    print_binary(byte);
    printf("\n");

    printf("\nUse bin:\n");

    bin(byte);
    printf("\n");

    printf("\nUse bin_recursive:\n");

    bin_recursive(byte);
    printf("\n");

    printf("\nUse bin_printf to print %u:\n", byte);

    char buf[33];
    buf[0] = '\0';
    bprintf(byte, buf);
    printf("76543210\n");
    printf("%8s\n", buf);

    printf("\nUse bin_printf:\n");

    bin_printf(byte);

    printf("bin_printf(1U << 5)\n");
    bin_printf(1U << 5);
}
