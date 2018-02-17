// http://www.cplusplus.com/forum/general/49079/

#include <iostream>

using std::cout;  using std::endl;

// This function takes things the C way
void print_array(double* xs, int cols, int rows=1)
{
  for (int r = 0; r < rows; r++)
  {
    for (int c = 0; c < cols; c++)
    {
      cout << xs[r*cols + c] << " ";
      // cout << *(xs + r*cols + c ) << " ";      // the same as xs[r*cols + c]
    }
    cout << "\n";
  }
}

// These overloads do things the C++ way
// (but we simply pass along to the C way)
template <int C>
  inline
void print_array( double (&xs)[ C ] )
{
  print_array( (double*)xs, C );
}

template <int C, int R>
  inline
void print_array( double (&xs)[ R ][ C ] )
{
  //-- print_array( (double*)xs, C, R );
  for (int irow=0; irow<R; ++irow) {
    for (int icol=0; icol<C; ++icol) {
      cout<< xs[irow][icol] << " ";
    }
    cout<<endl;
  }
}

int main()
{
  double d1     [ 5 ] =  { 1, 2, 3, 4, 5 };
  double d2[ 2 ][ 5 ] = {{ 1, 2, 3, 4, 5 },
    { 6, 7, 8, 9, 10 }};

  // The C way
  cout << "d1\n";  print_array( (double*)d1, 5 );
  cout << "d2\n";  print_array( (double*)d2, 5, 2 );

  cout << "\n";

  // The C++ way
  cout << "d1\n";  print_array( d1 );
  cout << "d2\n";  print_array( d2 );

  return 0;
}
