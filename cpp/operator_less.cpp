#include <functional>
#include <iostream>

using std::cout;    using std::endl;

// void DoWork(const std::binary_function<int, int, bool>& myOperator, int arg1, int arg2) {
//   cout<< "myOperator(arg1, arg2) = " << myOperator(arg1,arg2) <<endl;
// }

void DoWork(const std::binary_function<int, int, bool>& myOperator) {
  cout<< "myOperator(1, 2) = " << myOperator(1,2) <<endl; //--- does not work
}

// void DoWork(std::binary_function<bool(int, int)> myOperator,
//             int arg1, int arg2)
// {
//     if (myOperator(arg1, arg2)) {
//       cout<< "myOperator(arg1, arg2)" <<endl; //--- does not work
//     }
// }

int main()
{
    DoWork(std::less<int>());
    // DoWork(std::less<int>(), 100, 200);
    // DoWork(std::greater<int>(), 100, 200);

    return 0;
}
