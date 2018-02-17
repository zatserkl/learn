// read a file into memory
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  int length;
  char * buffer;

  ifstream is;

  cout<< "open file " << __FILE__ << " in binary mode" <<endl;
  is.open (__FILE__, ios::binary );

  is.seekg(0, ios::beg);
  cout<< "at the beginning of the file: is.tellg() = " << is.tellg() <<endl;

  // get length of file:
  is.seekg (0, ios::end);
  length = is.tellg();
  is.seekg (0, ios::beg);

  cout<< "length = " << length <<endl;

  // allocate memory:
  buffer = new char [length];

  // read data as a block:
  is.read (buffer,length);

  is.close();

  cout.write (buffer,length);

  return 0;
}
