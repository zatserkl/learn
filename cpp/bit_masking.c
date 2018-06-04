// https://www.indiabix.com/technical/c/bits-and-bytes/

/* Bit Masking */
/* Bit masking can be used to switch a character
   between lowercase and uppercase */
// NB: bug in the webpage code for CLR_FLAG: - (minus) instead of ~ (tilda)
#define BIT_POS(N)            ( 1U << (N) )
#define SET_FLAG(N, F)        ( (N) |= (F) )
#define CLR_FLAG(N, F)        ( (N) &= ~(F) )
#define TST_FLAG(N, F)        ( (N) & (F) )
#define BIT_RANGE(N, M)       ( BIT_POS((M) - (N) + 1) - 1 << (N) )
#define BIT_SHIFTL(B, N)      ( (unsigned)(B) << (N) )
#define BIT_SHIFTR(B, N)      ( (unsigned)(B) >> (N) )
#define SET_MFLAG(N, F, V)    ( CLR_FLAG(N, F), SET_FLAG(N, V) )
#define CLR_MFLAG(N, F)       ( (N) &= ~(F) )
#define GET_MFLAG(N, F)       ( (N) & (F) )

#include <stdio.h>
#include <string.h>

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

    // char buf[9];
    char buf[33];
    buf[0] = '\0';
    bprintf(n, buf);
    // printf("%8s\n", buf);
    char buf_byte[9];
    strncpy(buf_byte, buf, 8);
    buf_byte[8] = '\0';
    printf("%8s\n", buf_byte);
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

void main_fun()
{
    char a = 4;
    printf_byte(a);
    char a1 = (char) ~a;
    printf("%x\n", a1);
    printf_byte(a1);
    printf_int(a1);
}

void main_main()
{
    unsigned char ascii_char = 'A';        /*  char = 8 bits only */
    int test_nbr = 10;

    printf("Starting character = %c\n", ascii_char);
    /*  The 5th bit position determines if the character is
        uppercase or lowercase.
        5th bit = 0  - Uppercase
        5th bit = 1  - Lowercase
    */
    printf("\nTurn 5th bit on = %c\n", SET_FLAG(ascii_char, BIT_POS(5)) );
    printf("Turn 5th bit off = %c\n\n", CLR_FLAG(ascii_char, BIT_POS(5)) );

    printf("Look at shifting bits\n");
    printf("=====================\n");
    printf("Current value = %d\n", test_nbr);
    printf("Shifting one position left = %d\n",
           test_nbr = BIT_SHIFTL(test_nbr, 1) );
    printf("Shifting two positions right = %d\n",
           BIT_SHIFTR(test_nbr, 2) );

    printf("\nAZ\n");

    printf("BIT_POS:\nichar\tBIT_POS(ichar)\n");
    for (unsigned char ichar=0; ichar<8; ++ichar) {
        printf("%u\t%u\n", ichar, BIT_POS(ichar));
    }
    printf("\n");

    unsigned char a = 'a';
    printf("initial lower case char: %c in hex: %x\n", a, a);
    printf("turn to upper case char: %c in hex: %x\n", 'A', 'A');

    CLR_FLAG(a, BIT_POS(5));
    printf("After CLR_FLAG(a, BIT_POS(5)) char = %c in hex: %x\n", a, a);

}

int main()
{
    main_fun();
}
