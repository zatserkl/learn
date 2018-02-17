{
    // root -l sort_bubble.dat.C

    // gsqrt = new TGraph("sort_bubble.dat","%lg %*lg %lg");
    gsqrt = new TGraph(__FILE__,"%lg %*lg %lg");
    gsqrt->SetNameTitle("gsqrt","sort_bubble.dat;the number of elements;sqrt(elapsed time), #sqrt{s}");
    gsqrt->SetMarkerStyle(20);
    gsqrt->Draw("ap");
    fitp();
    // png("sort_bubble.dat");
}

# N     time    sqrt(time)

10000   0.359   0.599
20000   1.538   1.240
40000   6.266   2.503
80000   26.649  5.162
160000  105.950 10.293
