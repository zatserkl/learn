// g++ `$ROOTSYS/bin/root-config --cflags --glibs` -Wall Form.cpp

// based on ROOT chat http://root.cern.ch/root/roottalk/roottalk06/0537.html

// see also learn/const_char.cpp

#include <TString.h>	    // for ROOT's Form

#include <cstdio>           // for vsprintf
#include <cstdarg>          // for vi_list, vi_start, vi_end
#include <iostream>

using std::cout;      using std::endl;

// how works function Form: the first argument is string with format information, 
// which will be interpreted by vsprintf;
// the variable list is correspondent values.

const char* Form0(const char* f, ...)	// from learn/Form.cpp: simplified version, does not work well as the ROOT regular one 
{
  static char buf[1024];
  va_list ap;
  va_start(ap,f);         // initialize the va_list
  vsprintf(buf, f, ap);   // see commentary from cplusplus.com below
  va_end(ap);             // end vsprintf does not call the va_end macro
  return buf;
}

/* Comment to vsprintf from cplusplus.com

Writes into the array pointer by str a C string consisting in format with its format tags expanded to the values of the argument list arg formatted appropiately.
This function behaves exactly as sprintf except that the variable argument list is passed as a va_list instead of a succession of arguments, which becomes specially useful when the argument list to be passed comes itself from a variable argument list in the calling function.
vsprintf does not call the va_end macro.
*/

const char* fun(const char* text) {
  //-- static std::string str = text;	// NB: will be executed with just first call of the fun!
  static std::string str;
  str = text;				// will be executed every call of the fun
  cout<< "\t fun: text = " << text << " str = " << str <<endl;
  return str.c_str();
}

void two_strings(const char* str1, const char* str2) {
  cout<< "str1 = " << str1 << " str2 = " << str2 <<endl;
}

int main()
{
  int number = 10;
  cout<< Form0("the number is %d", number) <<endl;

  const char* string1 = fun("string1");
  cout<< "string1 = " << string1 <<endl;

  const char* string2 = fun("string2");
  cout<< "string2 = " << string2 <<endl;

  cout<< "after call with string2 string1 = " << string1 <<endl;

  two_strings(fun("first"), fun("second"));   // output: str1 = first str2 = first. NB: fun pars form stack

  cout<< "\nuse simplified Form0" <<endl;

  two_strings(Form0("first"), Form0("second"));   // output: 

  cout<< "\nuse regular ROOT's Form" <<endl;

  two_strings(Form("first"), Form("second"));   // output: 

  cout<< "\nuse regular ROOT's TString::Format use member Data()" <<endl;

  two_strings(TString::Format("first").Data(), TString::Format("second").Data());   // output: 

  cout<< "\nuse regular ROOT's TString::Format directly, w/o Data()" <<endl;

  two_strings(TString::Format("first"), TString::Format("second"));   // output: 

  return 0;
}
