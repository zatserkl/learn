#include <iostream>
#include <fstream>

using std::cout;      using std::endl;

const char* fname = "array2d_write_cpp.dat";

template <int ncol, int nrow>
inline void array_print_cpp(int (&a)[nrow][ncol])
{
  for (int irow=0; irow<nrow; ++irow) {
    for (int icol=0; icol<ncol; ++icol) {
      cout<< a[irow][icol] << " ";
    }
    cout<<endl;
  }
}

template <int ncol, int nrow>
inline void array_write_cpp(int (&a)[nrow][ncol])
{
  std::ofstream ofile(fname, std::ios::binary);
  for (int irow=0; irow<nrow; ++irow) {
    for (int icol=0; icol<ncol; ++icol) {
      ofile.write((char*) &a[irow][icol], sizeof(int));
      cout<< "a[" << irow << "][" << icol << "] = " << a[irow][icol] << " ";
    }
    cout<<endl;
  }
}

template <int ncol, int nrow>
inline void array_read_cpp(int (&a)[nrow][ncol])
{
  std::ifstream ifile(fname, std::ios::binary);
  for (int irow=0; irow<nrow; ++irow) {
    for (int icol=0; icol<ncol; ++icol) {
      ifile.read((char*) &a[irow][icol], sizeof(int));
      cout<< "a[" << irow << "][" << icol << "] = " << a[irow][icol] <<endl;
    }
    cout<<endl;
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

  cout<< "call array_print_cpp" <<endl;
  array_print_cpp(a);

  cout<< "call array_write_cpp" <<endl;
  array_write_cpp(a);

  int b[nrow][ncol];
  for (int irow=0; irow<nrow; ++irow) for (int icol=0; icol<ncol; ++icol) b[irow][icol] = 0;

  cout<< "call array_read_cpp for array b" <<endl;
  array_read_cpp(b);

  for (int irow=0; irow<nrow; ++irow) {
    for (int icol=0; icol<ncol; ++icol) {
      cout<< b[irow][icol] << " ";
    }
    cout<<endl;
  }

  return 0;
}
