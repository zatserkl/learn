#include "TF1.h"
#include "TMath.h"

Double_t myfunction(Double_t *x, Double_t *par)
{
   Double_t xx =x[0];
   Double_t f;
   const Double_t eps = 1.e-7;
   if (TMath::Abs(xx) > eps) {
      f = TMath::Abs(par[0]*TMath::Sin(par[1]*xx)/xx);
   } else {
      f = TMath::Abs(par[0]*par[1]);
   }
   return f;
}

void tf1_problem()
{
   Double_t ptmmax[2],par[2];
   Double_t yval;

   TF1 *fb = new TF1("fbb",myfunction,0.001,10.,2);
   fb->SetParameter(0,1.);
   fb->SetParameter(1,1.);
   fb->Draw();

   ptmmax[0]=2.0;
   par[0]=1.0;
   par[1]=2.0;

   // When you use the interpreter and call TF1::EvalPar you must specify
   // the address of the parameters array.
   // The doc says:
   //
   // WARNING. In case of an interpreted function (fType=2), it is the
   // user's responsability to initialize the parameters via InitArgs
   // before calling this function.
   // InitArgs should be called at least once to specify the addresses
   // of the arguments x and params.
   // InitArgs should be called everytime these addresses change.
   //
   // I have modified your code such that it works with or without the interpreter.
   // Rene Brun

   fb->InitArgs(ptmmax,fb->GetParameters());
   yval=fb->EvalPar(ptmmax,0);

   cout<< yval <<endl;
   yval=fb->EvalPar(ptmmax,par);
   cout<< yval <<endl;
}
