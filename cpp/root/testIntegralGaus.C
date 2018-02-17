#include "TF1.h"
#include "Math/GSLIntegrator.h"
#include "Math/WrappedTF1.h"
#include <iostream>



void testIntegralGaus() { 

   TF1 *g=new TF1("g","TMath::Gaus(x,0,0.1,1)",-100,100);
   double * params = 0; 
   double val1 = g->Integral(-9,9,params,1e-6);
   std::cout << "TF1::integral = " << val1 << std::endl; 
   // use GSL integration 
   // a small tolerance is sufficient otherwise rund-off errors will be dominant 
   ROOT::Math::GSLIntegrator ig(1.E-6,1.E-6,1000); 
   ROOT::Math::WrappedTF1 wf(*g); 
   ig.SetFunction(wf);
   double val2 = ig.Integral(-9,9);
   std::cout << "MathMore integral = " << val2 << std::endl; 

}
