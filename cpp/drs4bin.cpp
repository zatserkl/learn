/*
g++ -Wall drs4bin.cpp
./a.out drs4bin.cpp 0 10000
*/
#include <iostream>
#include <fstream>
#include <cstdarg>
#include <cstdlib>

using std::cout;      using std::endl;

int main(int argc, char *argv[])
{
  cout<< "argc = " << argc <<endl;  for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;

  if (argc < 3) {
    cout<< "Usage:\n" << argv[0] << " filename byte1 byte2" <<endl;
    return 0;
  }

  const char* ifname = argv[1];

  std::ifstream ifile(ifname, std::ios::binary);
  if (!ifile) {
    cout<< "File not found: " << ifname <<endl;
    return 0;
  }

  // get length of file:
  ifile.seekg (0, std::ios::end);
  int length = ifile.tellg();
  ifile.seekg (0, std::ios::beg);
  cout<< "file length = " << length <<endl;

  const int byte1 = std::atoi(argv[2]);    // atoi doesn't need std::
  const int byte2 = argc > 2? std::atoi(argv[3]): length;

  // read bytes into the buffer
  int start = byte1;
  int size = byte2 - byte1 + 1;
  if (size > length) size = length;

  char* buffer = 0;
  try {                       // NB: error w/o curved brackets {}
    buffer = new char[size];
  }
  catch (std::bad_alloc& bad_allocation) {
    cout<< "operator new exception caught: " << bad_allocation.what() <<endl;
    return 0;
  }

  for (int i=0; i<size; ++i) buffer[i] = '\0';    // don't need in the real world

  cout<< "read " << size << " bytes starting from byte " << start <<endl;
  ifile.seekg(start, std::ios::beg);
  ifile.read(buffer, size);

  ifile.close();

  cout.write(buffer, size);
  cout<<endl;

  return 0;
}
