{
    // root -l sort_insertion.dat.C

    // gsqrt = new TGraph("sort_insertion.dat","%lg %*lg %lg");
    gsqrt = new TGraph(__FILE__,"%lg %*lg %lg");
    gsqrt->SetNameTitle("gsqrt","sort_insertion.dat;the number of elements;sqrt(elapsed time), #sqrt{s}");
    gsqrt->SetMarkerStyle(20);
    gsqrt->Draw("ap");
    fitp();
    // png("sort_insertion.dat");
}

# N     time    sqrt(time)

10000   0.100   0.316
20000   0.396   0.629
40000   1.561   1.249
80000   6.219   2.494
160000  24.789  4.979
320000  99.496  9.975
