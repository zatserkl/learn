#include <cstdlib>
//? #include <cunistd>
#include <unistd.h>
#include <iostream>

using std::cout;   using std::endl;

main()
{
  int nseconds = 5;

  cout<< "Function sleep(int nseconds)" <<endl;
  cout<< "Details:" <<endl;
  cout<< "-------" <<endl;
  cout<< "include header file <cstdlib>" <<endl;
  cout<< "sleep is NOT a member of std namespace!" <<endl;
  cout<< "compiled: g++ " << __FILE__ <<endl<<endl;

  cout<< "Will wait nseconds = " << nseconds << " after \"Hello\"" <<endl<<endl;
  cout<< "Hello ";
  cout.flush();
  sleep(nseconds);
  cout<< "World!" <<endl;

  cout<<endl<< "--> now function usleep(int n_microseconds) from header <unistd> (for some reason it seems to be included in stdlib too ?!)" <<endl;
  int n_microseconds = 2000000;
  cout<< "Will wait n_microseconds = " << n_microseconds << " after \"Hello\"" <<endl<<endl;
  cout<< "Hello ";
  cout.flush();
  usleep(n_microseconds);
  cout<< "World!" <<endl;
}
