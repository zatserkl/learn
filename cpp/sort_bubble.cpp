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

void bubble(int N, int* a) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i=1; i<N; ++i) {
            if (a[i] < a[i-1]) {
                changed = true;
                int tmp = a[i];
                a[i] = a[i-1];
                a[i-1] = tmp;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        cout<< "Usage:\n" << argv[0] << " N" <<endl;
        return 0;
    }

    bool debug = false;

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

    bubble(N, a);

    if (debug) {
        std::copy(a, a+N, std::ostream_iterator<int>(cout, " "));
        cout<<endl;
    }

    delete[] a;
    return 0;
}

/*      To plot in ROOT
gsqrt = new TGraph("sort_bubble.dat","%lg %*lg %lg")
gsqrt->SetNameTitle("gsqrt","sort_bubble.dat;the number of elements;sqrt(elapsed time), #sqrt{s}")
gsqrt->SetMarkerStyle(20)
gsqrt->Draw("ap")
fitp()
png("sort_bubble.dat")
*/
