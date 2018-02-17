{
    // root -l sort_quicksort.dat.C

    g = new TGraph(__FILE__,"%lg %lg");
    g->SetNameTitle("g","sort_quicksort.dat;the number of elements;elapsed time, s");
    g->SetMarkerStyle(20);
    new TCanvas;
    g->Draw("ap");
    fitp();
    // png("sort_quicksort.dat");

    gsqrt = new TGraph(__FILE__,"%lg %*lg %lg");
    gsqrt->SetNameTitle("gsqrt","sort_quicksort.dat;the number of elements;sqrt(elapsed time), #sqrt{s}");
    gsqrt->SetMarkerStyle(20);
    new TCanvas;
    gsqrt->Draw("ap");
    fitp();
    // png("sort_quicksort_sqrt.dat");
}

# N     time    sqrt(time)

10000   0.005   0.071
20000   0.012   0.110
40000   0.034   0.184
80000   0.127   0.356
160000  0.479   0.692
320000  1.841   1.357
