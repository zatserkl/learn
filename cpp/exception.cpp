#include <iostream>
#include <iomanip>

using std::cout;      using std::endl;

// When declaring a function we can limit the exception type it might
// directly or indirectly throw by appending a throw suffix to the function declaration

enum ExceptionType {  // enum for simple control of exception type
  type_bool,
  type_int,
  type_char
};

void fun(ExceptionType type) throw (int, bool)  // this function can throw int and bool exceptions only
{
  switch (type) {
    case type_bool:
      cout<< "--- fun: throw exception of type bool" <<endl;
      throw true;
      break;
    case type_int:
      cout<< "--- fun: throw exception of type int" <<endl;
      throw 100;
      break;
    case type_char:
      // this exception will not be catched because this function is restricted
      // to throw int and bool exceptions only
      cout<< "--- fun: throw exception of type char which is not allowed me" <<endl;
      throw 'a';
      break;
  }
}

/*
learn> g++ exception.cpp
learn> ./a.out
--- fun_int: throw exception of type int
caught int exception 100
--- fun_int: throw exception of type char which is not allowed me
terminate called after throwing an instance of 'char'
Aborted
*/

main()
{
  ExceptionType type;
  
  try {
    type = type_int;
    fun(type);
  }
  catch (int e) {
    cout<< "caught int exception " << e <<endl;
  }
  catch (bool e) {
    cout<< "caught bool exception " << std::boolalpha << e <<endl;
  }
  catch (char e) {
    cout<< "caught char exception " << e <<endl;
  }
  catch (...) {
    cout<< "caught any exception" <<endl;
  }
  
  try {
    type = type_bool;
    fun(type);
  }
  catch (int e) {
    cout<< "caught int exception " << e <<endl;
  }
  catch (bool e) {
    cout<< "caught bool exception " << std::boolalpha << e <<endl;
  }
  catch (char e) {
    cout<< "caught char exception " << e <<endl;
  }
  catch (...) {
    cout<< "caught any exception" <<endl;
  }

  try {
    type = type_char;
    fun(type);
  }
  catch (int e) {
    cout<< "caught int exception " << e <<endl;
  }
  catch (bool e) {
    cout<< "caught bool exception " << std::boolalpha << e <<endl;
  }
  catch (char e) {
    cout<< "caught char exception " << e <<endl;
  }
  catch (...) {
    cout<< "caught any exception" <<endl;
  }
}
