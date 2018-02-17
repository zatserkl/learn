#include <iostream>

using std::cout;      using std::endl;

void fun(const char* ifname="default.dat", bool print=true)
{
  if (print) cout<< "ifname = " << ifname <<endl;
}

main()
{
  const char* ifname = "";
  bool print = true;

  fun(ifname,print);

  fun(ifname);

  fun();
}

/*
   If you specify any argument (even "") it will substitute default one:

learn$ ./a.out
ifname = 
ifname = 
ifname = default.dat
*/
