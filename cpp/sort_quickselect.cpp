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

//
// Lomuto algorithm
//

int partitionLomuto(int* a, int lo, int hi) {
    int pivot = a[hi];
    int insertion = lo;         // place for swapping
    for (int j=lo; j<hi; ++j) {
        if (a[j] <= pivot) {
            // swap a[insertion] and a[j]
            int tmp = a[insertion];
            a[insertion] = a[j];
            a[j] = tmp;
            ++insertion;        // increament the insertion point
        }
    }
    // place pivot in the middle: swap a[insertion] and a[hi]
    int tmp = a[insertion];
    a[insertion] = a[hi];
    a[hi] = tmp;
    
    return insertion;
}

void quicksortLomuto(int* a, int lo, int hi) {
    if (lo < hi) {
        int p = partitionLomuto(a, lo, hi);
        quicksortLomuto(a, lo, p-1);
        quicksortLomuto(a, p+1, hi);
    }
}

//
// Hoare algorithm: much better than Lomuto
//

// int partitionHoare(int* a, int lo, int hi)
// {
//     // original Hoare partition: much better than Lomuto
//     int pivot = a[lo];
//     int ilo = lo - 1;
//     int ihi = hi + 1;
//     while (true) {
//         // do --ihi;
//         // while (a[ihi] > pivot);     // find element in the second part which smaller than pivot
//         // do ++ilo;
//         // while (a[ilo] < pivot);     // find element in the first part which bigger than pivot
// 
//         while (a[--ihi] > pivot);     // find element in the second part which smaller than pivot
//         while (a[++ilo] < pivot);     // find element in the first part which bigger than pivot
// 
//         if (ilo < ihi) {
//             // swap elements: a[ilo] (bigger than pivot) with a[ihi] (smaller than pivot)
//             int tmp = a[ilo];
//             a[ilo] = a[ihi];
//             a[ihi] = tmp;
//         }
//         else return ihi;
//     }
// }

// int partitionHoare(int* a, int lo, int hi)
// {
//     int pivot = a[lo];
//     --lo;                           // use as an index
//     ++hi;                           // use as an index
//     while (true) {
//         while (a[--hi] > pivot);    // find element in the second part which smaller than pivot
//         while (a[++lo] < pivot);    // find element in the first part which bigger than pivot
// 
//         if (lo < hi) {
//             // swap elements: a[lo] (bigger than pivot) with a[hi] (smaller than pivot)
//             int tmp = a[lo];
//             a[lo] = a[hi];
//             a[hi] = tmp;
//         }
//         else return hi;
//     }
// }

// void quicksortHoare(int* a, int lo, int hi) {
//     if (lo < hi) {
//         int p = partitionHoare(a, lo, hi);
//         quicksortHoare(a, lo, p);
//         quicksortHoare(a, p+1, hi);
//     }
// }

int partitionHoare(int* a, int lo, int hi)
{
    int pivot = a[hi];
    while (lo < hi) {
        while (a[lo] < pivot) ++lo;     // find element in the first part which bigger than pivot
        while (a[hi] > pivot) --hi;     // find element in the second part which smaller than pivot

        if (a[lo] == a[hi]) lo++;       // avoid infinite loop in case of the equal elements
        else if (lo < hi)
        {
            int tmp = a[lo];
            a[lo] = a[hi];
            a[hi] = tmp;
        }
    }
    return hi;
}

void quicksortHoare(int* a, int lo, int hi) {
    if (lo < hi) {
        int p = partitionHoare(a, lo, hi);
        quicksortHoare(a, lo, p-1);
        quicksortHoare(a, p+1, hi);
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
    int* a = new int[N];

    if (debug && N > 20) {
        cout<< "turn off debug output" <<endl;
        debug = false;
    }

    arandom(N, a, 100);
    if (debug) {
        std::copy(a, a+N, std::ostream_iterator<int>(cout, " "));
        cout<<endl;
    }

    //cout<< "test partition" <<endl;
    //int p = partitionHoare(a, 0, N-1);
    //std::copy(a, a+N, std::ostream_iterator<int>(cout, " "));
    //cout<< "\np = " << p << " pivot = " << a[p] <<endl;
    //return 0;

    // quicksortLomuto(a, 0, N-1);
    quicksortHoare(a, 0, N-1);

    if (debug) {
        std::copy(a, a+N, std::ostream_iterator<int>(cout, " "));
        cout<<endl;
    }

    delete[] a;
    return 0;
}

/*      To plot in ROOT
gsqrt = new TGraph("sort_quicksort.dat","%lg %*lg %lg")
gsqrt->SetNameTitle("gsqrt","sort_quicksort.dat;the number of elements;sqrt(elapsed time), #sqrt{s}")
gsqrt->SetMarkerStyle(20)
gsqrt->Draw("ap")
fitp()
png("sort_quicksort.dat")
*/
