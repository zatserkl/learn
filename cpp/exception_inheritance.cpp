#include <iostream>
#include <exception>
#include <sstream>

using std::cout;      using std::endl;

class MyException: public std::exception
{
public:
  //
  // NB: constructor, destructor and what() should be defined with throw()
  //
  MyException() throw() {}
  MyException(const char* e) throw() {what_ = e;}
  virtual const char* what() const throw()
  {
    return std::string("MyException: " + what_).c_str();
    // // std::stringstream out("My exception happened: ");  //?? NB: content will be owrwritten!
    // // like:
    // // runtime exceptionened:
    // // see learn/stringstream_init.cpp
    //
    // std::stringstream out;
    // out << "MyException: ";
    // out << what_;
    // return out.str().c_str();
  }
  ~MyException() throw() {}
private:
  std::string what_;
//} myex;
};

int main () {
  try
  {
    //throw myex;
    throw MyException("runtime exception");
    // throw MyException();    // NB: type with ()
  }
  catch (std::exception& e)
  {
    cout << e.what() << endl;
  }
  return 0;
}
