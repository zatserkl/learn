/*
g++ `$ROOTSYS/bin/root-config --cflags --glibs` sort_cpp.C
*/

#include <TRint.h>
#include <TMath.h>

#include <iostream>

using std::cout;     using std::endl;

void sort_cpp()
{
   const int DIM = 5;
   Float_t x[DIM] = {3.0, 1.0, 2.0, 5.0, 4.0};
   // Float_t x[DIM] = {-3.0, -1.0, -2.0, -5.0, -4.0};
   Float_t y[DIM];
   
   for (int i=0; i<DIM; ++i) {
      y[i] = 10.*x[i];
      cout<< i <<" x = " << x[i] << " y = " << y[i] <<endl;
   }

   // Long64_t index[DIM];
   // Long64_t np = DIM;                  // Int_t is good as well
   Int_t index[DIM];                // CINT knows now TMath::Sort if index is Int_t
   Int_t np = DIM;

   TMath::Sort(np, x, index, kFALSE);  // kFALSE: increasing order

   Float_t xsort[DIM];
   Float_t ysort[DIM];
   for (int i=0; i<np; ++i) {
      xsort[i] = x[index[i]];
      ysort[i] = y[index[i]];
      cout<< i <<" xsort = " << xsort[i] << " ysort = " << ysort[i] <<endl;
   }
}

#ifndef __CINT__
main()
{
   sort_cpp();
}
#endif
