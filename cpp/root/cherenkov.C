double cherenkov_T(double theta_deg, double n=1.5, double m=0.938)
{
   // cos(theta) = 1/(beta*n)

   //double pi = acos(-1.);
   double theta = theta_deg*TMath::Pi()/180;
   double beta = 1/(n*cos(theta));

   double T = m / (1 - beta*beta) - m;
   cout<< "T = " << T << endl;
   return T;
}

/*
   To create TF1:
   TF1* fpar = new TF1("fpar", "Rpar(x);#theta_{i};R_{#parallel}", 0, 3.14/2)
   fpar->Draw();
*/
double Rpar(double theta_i, double n_i=1.5, double n_t=1.)
{
   // Reflection coefficient for E (polarization) in the incident plane
   // Rpar = (tan(theta_i - theta_t))^2 / (tan(thata_i + theta_t))^2
   // feature in case of theta_i + theta_t = pi/2

   if (theta_i < 0 || theta_i > TMath::Pi()/2.) {
      cout<< "Rpar: theta_i = " << theta_i << " is out of range (0, pi/2)" <<endl;
      return 0;
   }

   // n_i*sin(theta_i) = n_t*sin(theta_t)
   double theta_t = TMath::ASin((n_i/n_t)*TMath::Sin(theta_i));

   double Rpar = 0;
   const double eps = 1.e-7;
   if (TMath::Abs(theta_i + theta_t - TMath::Pi()/2.) > eps) {
      double tan_diff = TMath::Tan(theta_i-theta_t);
      double tan_sum = TMath::Tan(theta_i+theta_t);
      Rpar = (tan_diff*tan_diff) / (tan_sum*tan_sum);
   }
   return Rpar;
}

/*
   To create TF1:
   TF1* fpar_deg = new TF1("fpar_deg", "Rpar_deg(x);#theta_{i};R_{#parallel}", 0, 90)
   fpar_deg->SetLineColor(2)
   fpar_deg->Draw();
*/
double Rpar_deg(double theta_i_deg, double n_i=1.5, double n_t=1.)
{
   if (theta_i_deg < 0 || theta_i_deg > 90.) {
      cout<< "Rpar_deg: theta_i_deg = " << theta_i_deg << " is out of range (0, 90)" <<endl;
      return 0;
   }
   double theta_i = theta_i_deg*TMath::Pi()/180;
   return Rpar(theta_i, n_i, n_t);
}

/*
   To create TF1:
   TF1* fperp = new TF1("fperp", "Rperp(x);#theta_{i};R_{#perp}", 0, 3.14/2)
   fperp->Draw();
*/
double Rperp(double theta_i, double n_i=1.5, double n_t=1.)
{
   // Reflection coefficient for E (polarization) perpendicular to the incident plane
   // Rpar = (sin(theta_i - theta_t))^2 / (sin(thata_i + theta_t))^2

   if (theta_i < 0 || theta_i > TMath::Pi()/2.) {
      cout<< "Rpar: theta_i = " << theta_i << " is out of range (0, pi/2)" <<endl;
      return 0;
   }

   // n_i*sin(theta_i) = n_t*sin(theta_t)
   double theta_t = TMath::ASin((n_i/n_t)*TMath::Sin(theta_i));

   double sin_diff = TMath::Sin(theta_i - theta_t);
   double sin_sum = TMath::Sin(theta_i + theta_t);
   double Rperp = (sin_diff*sin_diff) / (sin_sum*sin_sum);
   return Rperp;
}

/*
   To create TF1:
   TF1* fperp_deg = new TF1("fperp_deg", "Rperp_deg(x);#theta_{i};R_{#perp}", 0, 90)
   fperp_deg->SetLineColor(4)
   fperp_deg->Draw();
*/
double Rperp_deg(double theta_i_deg, double n_i=1.5, double n_t=1.)
{
   if (theta_i_deg < 0 || theta_i_deg > 90.) {
      cout<< "Rperp_deg: theta_i_deg = " << theta_i_deg << " is out of range (0, 90)" <<endl;
      return 0;
   }
   double theta_i = theta_i_deg*TMath::Pi()/180;
   return Rperp(theta_i, n_i, n_t);
}

//
// Make a nice picture
//

void R_pic()
{
   //
   // quartz --> air: n_i = 1.5, n_t = 1
   //

   TF1* fpar_deg = new TF1("fpar_deg", "Rpar_deg(x);#theta_{i};R_{#parallel}", 0, 90);
   fpar_deg->SetLineColor(2);
   TF1* fperp_deg = new TF1("fperp_deg", "Rperp_deg(x);#theta_{i};R_{#perp}", 0, 90);
   fperp_deg->SetLineColor(4);

   // create clone to hold global title
   TF1* fperp = (TF1*) fperp_deg->Clone("fperp_deg_glob");
   fperp_deg_glob->SetTitle("R_{#parallel} and R_{#perp}  for boundary quartz #rightarrow air;#theta_{i};R_{#parallel}, R_{#perp}");

   new TCanvas;
   fperp_deg_glob->Draw();
   fpar_deg->Draw("same");

   TLegend* legend = new TLegend(0.60,0.50, 0.75,0.75);
   legend->SetFillColor(0);
   legend->SetBorderSize(0);
   legend->AddEntry(fpar_deg, "R_{#parallel}");
   legend->AddEntry(fperp_deg, "R_{#perp}");
   legend->Draw();

   //
   // air --> quartz n_i = 1, n_t = 1.5
   //

   TF1* fpar_deg1 = new TF1("fpar_deg1", "Rpar_deg(x,1,1.5);#theta_{i};R_{#parallel}", 0, 90);
   fpar_deg1->SetLineColor(2);
   TF1* fperp_deg1 = new TF1("fperp_deg1", "Rperp_deg(x,1,1.5);#theta_{i};R_{#perp}", 0, 90);
   fperp_deg1->SetLineColor(4);

   // create clone to hold global title
   TF1* fperp = (TF1*) fperp_deg1->Clone("fperp_deg1_glob");
   fperp_deg1_glob->SetTitle("R_{#parallel} and R_{#perp}  for boundary air #rightarrow quartz;#theta_{i};R_{#parallel}, R_{#perp}");

   new TCanvas;
   fperp_deg1_glob->Draw();
   fpar_deg1->Draw("same");

   TLegend* legend1 = new TLegend(0.20,0.50, 0.35,0.75);
   legend1->SetFillColor(0);
   legend1->SetBorderSize(0);
   legend1->AddEntry(fpar_deg1, "R_{#parallel}");
   legend1->AddEntry(fperp_deg1, "R_{#perp}");
   legend1->Draw();
}
