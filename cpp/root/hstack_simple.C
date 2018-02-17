{
   // From http://root.cern.ch/root/html526/THStack.html

   THStack hs("hs","test stacked histograms");
   TH1F *h1 = new TH1F("h1","test hstack",100,-4,4);
   h1->FillRandom("gaus",20000);
   h1->SetFillColor(kRed);
   hs.Add(h1);
   TH1F *h2 = new TH1F("h2","test hstack",100,-4,4);
   h2->FillRandom("gaus",15000);
   h2->SetFillColor(kBlue);
   hs.Add(h2);
   TH1F *h3 = new TH1F("h3","test hstack",100,-4,4);
   h3->FillRandom("gaus",10000);
   h3->SetFillColor(kGreen);
   hs.Add(h3);
   TCanvas c1("c1","stacked hists",10,10,700,900);
   c1.Divide(1,2);
   c1.cd(1);
   hs.Draw();
   c1.cd(2);
   hs->Draw("nostack");
}
