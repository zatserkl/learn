// vim: set paste ts=4

#include <string>
#include <iostream>

using std::cout;    std::endl;

main()
{
  // NB: TODO

  int some;             // to test vim :ilist
  // this is a comment
  //-- this is an important comment
  //this is a commented out line
  // regular comment again
  /// this is should be just regular comment
  
  // ROOT control comments
  int i1;   //!   not persistent
  int i2;   //[]  array
  int i3;   //->  reference
  int i4;   //||  something I forgot

  // this is some other comment
  for (int i=0; i<5; ++i) {
    cout<< i <<endl;
    // some other comment
    // some Tab here
    // tab from here:	:to here 2 tabs
    
    for (int j=0; j<2; ++j) {
      for (int k=0; k<2; ++k) {
	cout<< "xxx" <<endl;
	for (int l=0; l<2; ++l) {
	  // comment started from position 11

          // comment
	}
      }
    }
  }

  typedef int integer;
  typedef float real;

  std::string s1 = "This is a string";
  std::string s2 = " ";

  s2 = s1;
  cout<< "s2 = " << s2 <<endl;
}
