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

int main()
{
    srand(0);       // initialize random seed. NB: 1 is a special value to repeat the sequence.

    // generate numbers between 0 and 99
    for (int i=0; i<10; ++i) cout<< rand() % 100 <<endl;

    cout<< "use arandom" <<endl;

    // use arandom
    const int N = 10;
    int max = 100;
    int a[N];

    arandom(N, a, max, 0);

    // for (int i=0;i<N;++i) cout<< a[i] << " "; cout<<endl;

    cout<< "\nrandom array with the same values" <<endl;
    std::copy(a, a+N, std::ostream_iterator<int>(cout, "\n"));

    return 0;
}
