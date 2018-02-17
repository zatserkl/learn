#include <iostream>

using std::cout;      using std::endl;

int fun1(int a, int b) {
  return a;
}

int fun2(int a, int) {
  return a;
}

#ifndef __CINT__
main()
{
  cout<< fun1(1,2) <<endl;
  cout<< fun2(1,2) <<endl;
}
#endif

/* There is compiler warning just about the fun1 only

// .L not_used_arg.cpp+
Info in <TUnixSystem::ACLiC>: creating shared library /home/zatserkl/learn/./not_used_arg_cpp.so
In file included from /home/zatserkl/learn/not_used_arg_cpp_ACLiC_dict.h:34,
                 from /home/zatserkl/learn/not_used_arg_cpp_ACLiC_dict.cxx:17:
/home/zatserkl/learn/./not_used_arg.cpp:5: warning: unused parameter ‘b’
/home/zatserkl/learn/./not_used_arg.cpp:14: warning: ISO C++ forbids declaration of ‘main’ with no type
*/
