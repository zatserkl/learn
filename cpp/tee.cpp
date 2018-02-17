/*
To redirect into tee std error output as well

In sh-like shells, e.g. bash:

   ./a.out 2>&1 | tee tee.txt 

or in c-like shells, e.g. tcsh:

   ./a.out |& tee tee.txt
*/

#include <iostream>

using std::cout;      using std::endl;

main()
{
  cout<< "cout" <<endl;
  std::cerr<< "cerr" <<endl;
}
