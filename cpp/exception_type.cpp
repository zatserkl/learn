// Andriy Zatserklyaniy <zatserkl@gmail.com> Oct 14, 2018

#include <iostream>
#include <exception>

using std::cout;    using std::endl;

/** Important points:
  * 1) the method what should have quailifier const throw()
  * 2) you are throw an instance of the exception class e.g. MyExceptionType1()
  */

class MyExceptionType1: public std::exception {
public:
    const char* what() const throw() {
        return "this is MyExceptionType1::what()";
    }
};

class MyExceptionType2: public std::exception {
public:
    const char* what() const throw() {
        return "this is MyExceptionType2::what()";
    }
};

void fun(int arg)
{
    cout<< "fun: arg = " << arg <<endl;

    if (arg == 1) {
        cout<< "fun: throw instance of MyExceptionType1" <<endl;
        throw MyExceptionType1();
    }
    if (arg == 2) {
        cout<< "fun: throw instance of MyExceptionType2" <<endl;
        throw MyExceptionType2();
    }

    cout<< "fun: throw instance of default std::exception" <<endl;
    throw std::exception();
}

int main()
{
    int arg;
    arg = 1;        // to produce an exception of type of MyExceptionType1
    arg = 2;        // to produce an exception of type of MyExceptionType2
    // arg = 0;        // to produce an exception of type of std::exception

    try {
        fun(arg);
    }
    catch(MyExceptionType1& e) {
        cout<< "Caught MyExceptionType1, e: " << e.what() <<endl;
    }
    catch(MyExceptionType2& e) {
        cout<< "Caught MyExceptionType2, e: " << e.what() <<endl;
    }

    catch(std::exception& e) {
        cout<< "Caught std::exception, e: " << e.what() <<endl;
    }
    catch(...) {
        // you reach this point if you comment out catch(std::exception& e) {}
        cout<< "Caught default exception with eclipsis ... as parameter" <<endl;
    }

    cout<< "Goodbye!" <<endl;
}
