// this example shows that std::string allocates memory for the data in heap
// and will not overwrite the next array element

#include <string>
#include <iostream>

using std::cout;      using std::endl;

void fill(std::string& str, const std::string& element, int n) {
  for (int i=0; i<n; ++i) {
    str += element;
  }
}

main()
{
  std::string array[3];
  // fill the second string with one letter
  array[1] = "b";
  // make the second string very long
  fill(array[0], "a", 1000);

  for (int i=0; i<3; ++i) {
    cout<< "--- string " << i <<endl;
    cout<< array[i] <<endl;
  }
}
