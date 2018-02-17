#include <iostream>
#include <fstream>

using std::cout;      using std::endl;

const char* fname = "array2d_write_c.dat";

void array_print_c(int* a, int ncol, int nrow=1)  // needs explicit type conversion (int*)a
{
  for (int irow=0; irow<nrow; ++irow) {
    for (int icol=0; icol<ncol; ++icol) {
      cout<< a[irow*ncol + icol] << " ";
    }
    cout<<endl;
  }
}

void array_write_c(int* a, int ncol, int nrow=1)  // needs explicit type conversion (int*)a
{
  std::ofstream ofile(fname, std::ios::binary);
  for (int irow=0; irow<nrow; ++irow) {
    for (int icol=0; icol<ncol; ++icol) {
      // ofile << a[irow*ncol + icol];      // NB: writes formatted output (characters)
      ofile.write((char*) &a[irow*ncol + icol], sizeof(int));
      cout<< "a[" << irow << "*" << ncol << " + " << icol << "] = " << a[irow*ncol + icol] <<endl;
    }
  }
}

int main()
{
  const int nrow = 2;
  const int ncol = 3;
  int a[nrow][ncol];

  for (int irow=0; irow<nrow; ++irow) {
    for (int icol=0; icol<ncol; ++icol) {
      a[irow][icol] = (irow+1)*10 + icol+1;
      cout<< a[irow][icol] << " ";
    }
    cout<<endl;
  }

  cout<< "call array_print" <<endl;
  array_print_c((int*)a, ncol, nrow);

  cout<< "call array_write" <<endl;
  array_write_c((int*)a, ncol, nrow);

  return 0;
}
