/*
clang -Wall
*/

#include <stdio.h>

//   // This is a mistake similar to "Making Embedded Systems", Chapter 2, p.26
//   struct {
//       int a;
//       int b;
//   } StructObj;                   //--NB: StructObj is a variable of type struct{int a; int b;};
//   static struct StructObj s1;


struct Struct {                 //--NB: standard definition of C struct, to use: struct Struct s1;
    int a;
    int b;
};

static struct Struct s2;


typedef struct {                //--NB: typedef struct
    int a;
    int b;
} StructType;                   // StructType is a type here, cf. typedef int Int_t

static StructType s3;           //--NB: no keyword 'struct' in this declaration


// add a name after the keyword 'struct'

typedef struct StructTypeName { //--NB: typedef struct StructTypeName NB 2: it's fine to use the same name
    int a;
    int b;
} StructTypeName;               // StructTypeName is a type here, cf. typedef int Int_t

static StructTypeName s4;       //--NB: no keyword 'struct' in this declaration


// use different names after the keyword 'struct' and for type name

typedef struct StructTypeName1{     //--NB: typedef struct StructTypeName
    int a;
    int b;
} StructTypeName2;                  // StructTypeName is a type here, cf. typedef int Int_t

static struct StructTypeName1 s5;   //--NB: keyword 'struct'    NB 2: the name StructTypeName1 is fine
static StructTypeName2 s6;          //--NB: no keyword 'struct': it will be an error with 'struct'


int main() {
    printf("Hello C!\n");

    s2.a = 1;
    s2.b = 2;
    printf("s2.a + s2.b = %d\n", s2.a+s2.b);

    s3.a = 1;
    s3.b = 2;
    printf("s3.a + s3.b = %d\n", s3.a+s3.b);

    s4.a = 1;
    s4.b = 2;
    printf("s4.a + s4.b = %d\n", s4.a+s4.b);

    s5.a = 1;
    s5.b = 2;
    printf("s5.a + s5.b = %d\n", s5.a+s5.b);

    s6.a = 1;
    s6.b = 2;
    printf("s6.a + s6.b = %d\n", s6.a+s6.b);

    return 0;
}
