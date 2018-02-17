/*
root -l -q sortxy.C
*/
#include <TMath.h>
#include <iostream>

using std::cout;        using std::endl;

void sortxy()
{
   Float_t x[5] = {2,  1,  5,  4,  3};
   Float_t y[5] = {20, 10, 50, 40, 30};
   
   const Long64_t np = 5;
   Long64_t index[np];
   // Long64_t index[1000];
   
   TMath::Sort(np, x, index, 0);
   
   for (int i=0; i<np; ++i) {
      cout<< "index[i] = " << index[i] << " x[index[i]] = " << x[index[i]] << " y[index[i]] = " << y[index[i]] <<endl;
   }
}
