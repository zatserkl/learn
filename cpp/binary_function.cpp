// binary_function example
#include <iostream>
#include <functional>
using namespace std;

struct Compare : public binary_function<int,int,bool> {
  bool operator() (int a, int b) {return (a==b);}
};

int main () {
  Compare Compare_object;
  Compare::first_argument_type input1;
  Compare::second_argument_type input2;
  Compare::result_type result;

  cout << "Please enter first number: ";
  cin >> input1;
  cout << "Please enter second number: ";
  cin >> input2;

  result = Compare_object (input1,input2);

  cout << "Numbers " << input1 << " and " << input2;
  if (result)
	  cout << " are equal.\n";
  else
	  cout << " are not equal.\n";

  return 0;
}
