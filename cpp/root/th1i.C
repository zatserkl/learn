void th1i()
{
   TH1I* hall = new TH1I("hall","hall",5,0,5);
   hall->SetFillColor(4);
   for (int itimes=0; itimes<3; ++itimes) {
      for (int i=0; i<4; ++i) {
         hall->Fill(i);
      }
   }
   new TCanvas;
   hall->Draw();

   TH1I* hgood = new TH1I("hgood","hgood",5,0,5);
   hgood->SetFillColor(2);
   hgood->SetBinContent(1,3);
   hgood->SetBinContent(2,2);
   hgood->SetBinContent(3,1);
   hgood->SetBinContent(4,1);
   hgood->SetBinContent(5,0);

   new TCanvas;
   hgood->Draw();

   //TH1F* hallF = new TH1F("hallF", hall->GetTitle(), hall->GetNbinsX(), hall->GetXaxis()->GetXmin(), hall->GetXaxis()->GetXmax());

   TH1F* hallF = new TH1F(
         Form("%sF",hall->GetName()), 
         hall->GetTitle(), 
         hall->GetNbinsX(),
         hall->GetXaxis()->GetXmin(),
         hall->GetXaxis()->GetXmax()
   );
   TH1F* hgoodF = new TH1F(
         Form("%sF",hgood->GetName()), 
         hgood->GetTitle(), 
         hgood->GetNbinsX(),
         hgood->GetXaxis()->GetXmin(),
         hgood->GetXaxis()->GetXmax()
   );

   // Histogram bins runs from 1 to GetNbinsX()
   // bin 0 is underflow
   // bin GetNbinsX()+1 is iverflow
   for (int i=0; i<=hall->GetNbinsX()+1; ++i) {
      hallF->SetBinContent(i, hall->GetBinContent(i));
      hallF->SetBinError(i, hall->GetBinError(i));
   }
   for (int i=0; i<=hgood->GetNbinsX()+1; ++i) {
      hgoodF->SetBinContent(i, hgood->GetBinContent(i));
      hgoodF->SetBinError(i, hgood->GetBinError(i));
   }

   new TCanvas;
   hallF->Draw("hist");
   new TCanvas;
   hgoodF->Draw("hist");

   TH1F* heff = (TH1F*) hallF->Clone("heff");
   heff->SetTitle("efficiency");
   heff->Reset();
   heff->Divide(hgoodF, hallF, 1, 1, "B");

   new TCanvas;
   heff->Draw();
}
