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

void insertion(int N, int* a) {
    for (int i=1; i<N; ++i) {
        for (int j=i; j>0; --j) {
            if (a[j] < a[j-1]) {
                int tmp = a[j];
                a[j] = a[j-1];
                a[j-1] = tmp;
            }
            else break;
        }
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

    insertion(N, a);

    if (debug) {
        std::copy(a, a+N, std::ostream_iterator<int>(cout, " "));
        cout<<endl;
    }

    delete[] a;
    return 0;
}

/*      To plot in ROOT
gsqrt = new TGraph("sort_insertion.dat","%lg %*lg %lg")
gsqrt->SetNameTitle("gsqrt","sort_insertion.dat;the number of elements;sqrt(elapsed time), #sqrt{s}")
gsqrt->SetMarkerStyle(20)
gsqrt->Draw("ap")
fitp()
png("sort_insertion.dat")
*/
