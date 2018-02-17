void fitLL()
{
   Float_t x[1000];
   Float_t y[1000];
   Int_t np;
   
   Float_t x1 = -5;
   Float_t x2 =  5;
   Float_t dx = 0.2;

   Float_t xcurr = x1;
   Bool_t odd = kTRUE;
   np = 0 - 1;
   while (xcurr < x2) {
      ++np;
      xcurr += dx;
      x[np] = xcurr;
      odd = !odd;
      if (odd) y[np] = 0;
      else y[np] = xcurr*xcurr;
   }
   cout<< "np = " << np <<endl;

   TGraph* gr = new TGraph(np, x, y);
   gr->SetMarkerStyle(6);
   gr->SetMarkerColor(2);

   gr->Draw("awp");
}
