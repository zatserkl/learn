// http://stackoverflow.com/questions/6221965/c-multi-dimensional-array-function-parameter
// http://www.cppforschool.com/tutorial/array2.html

#include <iostream>

using std::cout;      using std::endl;

  template<std::size_t N, std::size_t M>
void func(int (&arr)[N][M])
{
  // for statically declared arrays

  cout << "int[" << N << "][" << M << "]\n";
  for (size_t n = 0; n != N; ++n)
    for (size_t m = 0; m != M; ++m)
      cout << arr[n][m] << ' ';
  cout << '\n' << endl;
}

void func2(int a[][2], int row, int col) {  // NB: a[][2]
  for (int irow=0; irow<row; ++irow) {
    for (int icol=0; icol<col; ++icol) {
      cout<< a[irow][icol] << " ";
    }
    cout<<endl;
  }
}

void func3(int a[][3], int row, int col) {  // NB: a[][3]
  for (int irow=0; irow<row; ++irow) {
    for (int icol=0; icol<col; ++icol) {
      cout<< a[irow][icol] << " ";
    }
    cout<<endl;
  }
}

int main()
{
  int i1[2][3] = { { 4, 5, 6 }, { 7, 8, 9 } };
  int i2[4][2] = { { 1, 3 }, { 5, 7 }, { 9, 11 }, { 13, 15 } };
  func(i1);
  func(i2);

  cout<< "func2" <<endl;
  func2(i2, 4, 2);

  cout<< "func3" <<endl;
  func3(i1, 2, 3);
  return 0;
}
