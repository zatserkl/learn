#include <iostream>
#include <vector>

using std::cout;      using std::endl;

std::vector<std::vector<int> > random_matrix(unsigned nrows, unsigned ncols) {
    std::vector<std::vector<int> > m(nrows);
    for (unsigned irow=0; irow<nrows; ++irow) m[irow].resize(ncols);

    for (unsigned irow=0; irow<nrows; ++irow) {
        for (unsigned icol=0; icol<ncols; ++icol) {
            m[irow][icol] = (irow+1)*10 + (icol+1);
            cout<< "m[" << irow << "][" << icol << "] = " << m[irow][icol] <<endl;
        }
    }
    return m;
}

int main()
{
    unsigned nrows = 3;
    unsigned ncols = 4;

    // std::vector<std::vector<int> > m(nrows);
    // for (unsigned irow=0; irow<nrows; ++irow) m[irow].resize(ncols);

    std::vector<int> tmp(nrows,0);
    std::vector<std::vector<int> > m(ncols, tmp);

    for (unsigned irow=0; irow<nrows; ++irow) {
        for (unsigned icol=0; icol<ncols; ++icol) {
            m[irow][icol] = (irow+1)*10 + (icol+1);
            cout<< "m[" << irow << "][" << icol << "] = " << m[irow][icol] <<endl;
        }
    }

    for (unsigned irow=0; irow<nrows; ++irow) {
        for (unsigned icol=0; icol<ncols; ++icol) {
            cout<< m[irow][icol] << "   ";
        }
        cout<<endl;
    }

    return 0;
}
