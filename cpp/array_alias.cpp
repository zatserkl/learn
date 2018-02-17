#include <iostream>

using std::cout;      using std::endl;

main()
{
  int par[10];

  int npar = 0;
  int& par_a = par[npar++];
  int& par_b = par[npar++];
  int& par_c = par[npar++];

  par_a = 1;
  par_b = 2;
  par_c = 3;

  for (int i=0; i<npar; ++i) {
    cout<< "par[" << i << "] = " << par[i] <<endl;
  }
}
