// from http://www.gibmonks.com/c_plus/ch11lev1sec8.html

  // Fig. 11.6: Array.h
  // Array class for storing arrays of integers.
  #ifndef ARRAY_H
  #define ARRAY_H

  #include <iostream>
  using std::ostream;
  using std::istream;

  class Array
  {
     friend ostream &operator<<( ostream &, const Array & );
     friend istream &operator>>( istream &, Array & );      
  public:
     Array( int = 10 ); // default constructor
     Array( const Array & ); // copy constructor
     ~Array(); // destructor                    
     int getSize() const; // return size

     const Array &operator=( const Array & ); // assignment operator
     bool operator==( const Array & ) const; // equality operator   

     // inequality operator; returns opposite of == operator     
     bool operator!=( const Array &right ) const                 
     {                                                           
        return ! ( *this == right ); // invokes Array::operator==
     } // end function operator!=                                

     // subscript operator for non-const objects returns modifiable lvalue
     int &operator[]( int );                                              

     // subscript operator for const objects returns rvalue
     int operator[]( int ) const;                          
  private:
     int size; // pointer-based array size
     int *ptr; // pointer to first element of pointer-based array
  }; // end class Array

  #endif

///////////////////////////////////////////////////////////

   // Fig 11.7: Array.cpp
   // Member-function definitions for class Array
   #include <iostream>
   using std::cerr;
   using std::cout;
   using std::cin;
   using std::endl;

   #include <iomanip>
   using std::setw;

   #include <cstdlib> // exit function prototype
   using std::exit;

   //-- #include "Array.h" // Array class definition

   // default constructor for class Array (default size 10)
   Array::Array( int arraySize )
   {
      size = ( arraySize > 0 ? arraySize : 10 ); // validate arraySize
      ptr = new int[ size ]; // create space for pointer-based array

      for ( int i = 0; i < size; i++ )
         ptr[ i ] = 0; // set pointer-based array element
   } // end Array default constructor

   // copy constructor for class Array;
   // must receive a reference to prevent infinite recursion
   Array::Array( const Array &arrayToCopy )
      : size( arrayToCopy.size )
   {
      ptr = new int[ size ]; // create space for pointer-based array

      for ( int i = 0; i < size; i++ )
         ptr[ i ] = arrayToCopy.ptr[ i ]; // copy into object
   } // end Array copy constructor

   // destructor for class Array
   Array::~Array()
   {
      delete [] ptr; // release pointer-based array space
   } // end destructor

   // return number of elements of Array
   int Array::getSize() const
   {
      return size; // number of elements in Array
   } // end function getSize

   // overloaded assignment operator;
   // const return avoids: ( a1 = a2 ) = a3
   const Array &Array::operator=( const Array &right )
   {
      if ( &right != this ) // avoid self-assignment
      {
         // for Arrays of different sizes, deallocate original
         // left-side array, then allocate new left-side array
         if ( size != right.size )
         {
            delete [] ptr; // release space
            size = right.size; // resize this object
            ptr = new int[ size ]; // create space for array copy
         } // end inner if

         for ( int i = 0; i < size; i++ )
            ptr[ i ] = right.ptr[ i ]; // copy array into object
      } // end outer if

      return *this; // enables x = y = z, for example
   } // end function operator=

   // determine if two Arrays are equal and
   // return true, otherwise return false
   bool Array::operator==( const Array &right ) const
   {
      if ( size != right.size )
         return false; // arrays of different number of elements

      for ( int i = 0; i < size; i++ )
         if ( ptr[ i ] != right.ptr[ i ] )
            return false; // Array contents are not equal

      return true; // Arrays are equal
   } // end function operator==

   // overloaded subscript operator for non-const Arrays;
   // reference return creates a modifiable lvalue
   int &Array::operator[]( int subscript )
   {
      // check for subscript out-of-range error
      if ( subscript < 0 || subscript >= size )
      {
         cerr << "\nError: Subscript " << subscript
            << " out of range" << endl;
         exit( 1 ); // terminate program; subscript out of range
      } // end if

      return ptr[ subscript ]; // reference return
   } // end function operator[]

  // overloaded subscript operator for const Arrays
  // const reference return creates an rvalue
  int Array::operator[]( int subscript ) const
  {
     // check for subscript out-of-range error
     if ( subscript < 0 || subscript >= size )
     {
        cerr << "\nError: Subscript " << subscript
           << " out of range" << endl;
        exit( 1 ); // terminate program; subscript out of range
     } // end if

     return ptr[ subscript ]; // returns copy of this element
  } // end function operator[]

  // overloaded input operator for class Array;
  // inputs values for entire Array
  istream &operator>>( istream &input, Array &a )
  {
     for ( int i = 0; i < a.size; i++ )
        input >> a.ptr[ i ];

     return input; // enables cin >> x >> y;
  } // end function

  // overloaded output operator for class Array
  ostream &operator<<( ostream &output, const Array &a )
  {
     int i;

     // output private ptr-based array
     for ( i = 0; i < a.size; i++ )
     {
        output << setw( 12 ) << a.ptr[ i ];

        if ( ( i + 1 ) % 4 == 0 ) // 4 numbers per row of output
           output << endl;
     } // end for

     if ( i % 4 != 0 ) // end last line of output
        output << endl;

     return output; // enables cout << x << y;
  } // end function operator<<

///////////////////////////////////////////////////////////

  // Fig. 11.8: fig11_08.cpp
  // Array class test program.
  #include <iostream>
  using std::cout;
  using std::cin;
  using std::endl;

  //-- #include "Array.h"

  int main()
  {
     Array integers1( 7 ); // seven-element Array   
     Array integers2; // 10-element Array by default

     // print integers1 size and contents
     cout << "Size of Array integers1 is "
        << integers1.getSize()
        << "\nArray after initialization:\n" << integers1;

     // print integers2 size and contents
     cout << "\nSize of Array integers2 is "
        << integers2.getSize()
        << "\nArray after initialization:\n" << integers2;

     // input and print integers1 and integers2
     cout << "\nEnter 17 integers:" << endl;
     cin >> integers1 >> integers2;

     cout << "\nAfter input, the Arrays contain:\n"
        << "integers1:\n" << integers1
        << "integers2:\n" << integers2;

     // use overloaded inequality (!=) operator
     cout << "\nEvaluating: integers1 != integers2" << endl;

     if ( integers1 != integers2 )
        cout << "integers1 and integers2 are not equal" << endl;

     // create Array integers3 using integers1 as an          
     // initializer; print size and contents                  
     Array integers3( integers1 ); // invokes copy constructor

     cout << "\nSize of Array integers3 is "
        << integers3.getSize()
        << "\nArray after initialization:\n" << integers3;

     // use overloaded assignment (=) operator
     cout << "\nAssigning integers2 to integers1:" << endl;
     integers1 = integers2; // note target Array is smaller

     cout << "integers1:\n" << integers1
        << "integers2:\n" << integers2;

     // use overloaded equality (==) operator
     cout << "\nEvaluating: integers1 == integers2" << endl;

     if ( integers1 == integers2 )
        cout << "integers1 and integers2 are equal" << endl;

     // use overloaded subscript operator to create rvalue
     cout << "\nintegers1[5] is " << integers1[ 5 ];

     // use overloaded subscript operator to create lvalue
     cout << "\n\nAssigning 1000 to integers1[5]" << endl;
     integers1[ 5 ] = 1000;
     cout << "integers1:\n" << integers1;

     // attempt to use out-of-range subscript
     cout << "\nAttempt to assign 1000 to integers1[15]" << endl;
     integers1[ 15 ] = 1000; // ERROR: out of range
     return 0;
  } // end main

/*
Size of Array integers1 is 7
Array after initialization:
           0           0           0           0
           0           0           0
Size of Array integers2 is 10
Array after initialization:
           0           0           0           0
           0           0           0           0
           0           0

Enter 17 integers:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17

After input, the Arrays contain:
integers1:
           1           2           3           4
           5           6           7
integers2:
           8           9          10          11
          12          13          14          15
          16          17

Evaluating: integers1 != integers2
integers1 and integers2 are not equal

Size of Array integers3 is 7
Array after initialization:
           1           2           3           4
           5           6           7

Assigning integers2 to integers1:
integers1:
           8           9          10          11
          12          13          14          15
          16          17
integers2:
           8           9          10          11
          12          13          14          15
          16          17

Evaluating: integers1 == integers2
integers1 and integers2 are equal

integers1[5] is 13

Assigning 1000 to integers1[5]
integers1:
           8           9          10          11
          12        1000          14          15
          16          17

Attempt to assign 1000 to integers1[15]

Error: Subscript 15 out of range
*/
