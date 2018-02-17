/*
root -l 'STM_pe.C("STM_32const.out",28.2,10000,"b1>6000")'
*/
void STM_pe(const char* ifname="STM_32const.out", double ped=28.2, double b1_0=0, TCut cut="")    // for 32V cut=b1>6000
{
   const char tname[] = "tpe";
   TTree* t = splin(ifname, tname);

   new TCanvas;
   TH2* hpe = (TH2*) gDirectory->Get("hpe");
   if (hpe) {
      hpe->SetDirectory(0);
      delete hpe;
   }
   t->Draw("a1:b1>>hpe", cut);
   hpe = (TH2*) gDirectory->Get("hpe");

   // reference value
   if (b1_0 == 0) b1_0 = hpe->GetMean(1);

   hpe->Fit("pol1");

   // fit parameters
   //Double_t intersect = hpe->GetFunction("pol1")->GetParameter(0);
   Double_t slope = hpe->GetFunction("pol1")->GetParameter(1);

   new TCanvas;
   std::stringstream ss;
   ss.str("");
   ss.setf(std::ios::showpos);      // ss << std::showpos does not work in ROOT
   ss
      << "a1-("
      << slope
      << ")"
   ;
   ss.unsetf(std::ios::showpos);    // ss << std::noshowpod does not work in ROOT
   ss
      << "*(b1-"
      << b1_0 << ")"
   ;
   //cout<< ss.str() <<endl;        // a1+0.0150717*(b1-10000)

   t->Draw(ss.str().c_str(), cut);
   TH1* hcorr = t->GetHistogram();
   hcorr->Fit("gaus");

   Double_t gmean = hcorr->GetFunction("gaus")->GetParameter(1);
   Double_t gsigma = hcorr->GetFunction("gaus")->GetParameter(2);
   cout<< "--> Fit parameters: gmean = " << gmean << " gsigma = " << gsigma <<endl;
   
   Double_t npe = ((gmean-ped)/gsigma)*((gmean-ped)/gsigma);
   cout<< "Npe = " << npe <<endl;
}
