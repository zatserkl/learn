#include <iostream>
#include <cstdarg>

using std::cout;      using std::endl;

main(int argc, char *argv[])
{
  cout<< "argc = " << argc <<endl;  for (int i=0; i<argc; ++i) cout<< i <<" "<< argv[i] <<endl;

  if (argc == 1) {
    cout<< "Usage:" <<endl;
    cout<< argv[0] << " arg1 arg2 ... " <<endl;
    return 0;
  }
}
