#include <iostream>
#include <cstdlib>
#include <algorithm>

using std::cout;      using std::endl;

void arandom(int N, int* a, int max, int seed=0)
{
    // generates 0..max-1

    srand(seed);    // initialize random seed. NB: 1 is a special value to repeat the sequence.

    // generate numbers between 0 and max-1
    for (int i=0; i<N; ++i) a[i] = rand() % max;
}

void merge(int a[], int lo, int hi)
{
    int mid = lo + (hi - lo)/2;
    int ilo = lo;                   // counter in the left part, before the middle
    int ihi = mid + 1;              // counter in the right part, after the middle

    int buf[hi - lo + 1];
    int ibuf = 0;

    // merge in sorted form the two arrays
    while (ilo <= mid && ihi <= hi) {
        if (a[ilo] < a[ihi])
            buf[ibuf++] = a[ilo++];
        else
            buf[ibuf++] = a[ihi++];
    }

    // merge the remining elements in the left array
    while (ilo <= mid) buf[ibuf++] = a[ilo++];

    // merge the remining elements in the right array
    while (ihi <= hi) buf[ibuf++] = a[ihi++];

    // move from temporary array back to the master array
    for (int i=lo; i<=hi; ++i) a[i] = buf[i-lo];
}

void merge_sort(int a[], int lo, int hi)
{
    if (lo < hi) {
        int mid = lo + (hi - lo)/2;

        merge_sort(a, lo, mid);
        merge_sort(a, mid+1, hi);
        merge(a, lo, hi);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        cout<< "Usage:\n" << argv[0] << " N" <<endl;
        return 0;
    }

    bool debug = true;

    int N = std::atoi(argv[1]);
    //-- int* a = new int[N];
    int a[N];                               // g++ extension

    if (debug && N > 20) {
        cout<< "turn off debug output" <<endl;
        debug = false;
    }

    arandom(N, a, 100);
    if (debug) {
        std::copy(a, a+N, std::ostream_iterator<int>(cout, " "));
        cout<<endl;
    }

    merge_sort(a, 0, N-1);

    if (debug) {
        std::copy(a, a+N, std::ostream_iterator<int>(cout, " "));
        cout<<endl;
    }

    //-- delete[] a;
    return 0;
}

/*      To plot in ROOT
gsqrt = new TGraph("sort_merge.dat","%lg %*lg %lg")
gsqrt->SetNameTitle("gsqrt","sort_merge.dat;the number of elements;sqrt(elapsed time), #sqrt{s}")
gsqrt->SetMarkerStyle(20)
gsqrt->Draw("ap")
fitp()
png("sort_merge.dat")
*/
