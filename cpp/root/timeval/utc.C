void utc()
{
   Double_t a = time(NULL);
   Double_t x[]={a,a+60,a+120,a+180,a+240};
   Double_t y[]={1,2,3,4,5};
   TGraph *g = new TGraph(5,x,y);
   g->GetXaxis()->SetTimeDisplay(1);
   g->GetXaxis()->SetTimeFormat("%H:%M:%S");
   g->Draw("A*");
}
