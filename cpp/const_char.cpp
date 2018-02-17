// g++ `$ROOTSYS/bin/root-config --cflags --glibs` -Wall const_char.cpp

#include <iostream>
#include <string>

#include <cstdarg>
#include <cstdio>

#include <TString.h>

using std::cout;      using std::endl;

const char* fun(const char* text) {
  //-- static std::string str = text;	// NB: will be executed with just first call of the fun!
  static std::string str;
  str = text;				// will be executed every call of the fun
  cout<< "\t fun: text = " << text << " str = " << str <<endl;
  return str.c_str();
}

const char* Form0(const char* f, ...)	// from learn/Form.cpp: simplified version, does not work well as the ROOT regular one
{
  static char buf[1024];
  va_list ap;
  va_start(ap,f);         // initialize the va_list
  vsprintf(buf, f, ap);   // see commentary from cplusplus.com below
  va_end(ap);             // end vsprintf does not call the va_end macro
  return buf;
}

void two_strings(const char* str1, const char* str2) {
  cout<< "str1 = " << str1 << " str2 = " << str2 <<endl;
}

int main()
{
  const char* ifname = "run033.out";	  // ifname points to the string which compiler allocates in the STATIC memory
  cout<< "ifname = " << ifname <<endl;

  const char ifname1[] = "run033.out";	  // ifname1 is pointer to the LOCAL array. The string will be copied in the array
  cout<< "ifname1 = " << ifname1 <<endl;

  const char* string1 = fun("string1");
  cout<< "string1 = " << string1 <<endl;

  const char* string2 = fun("string2");
  cout<< "string2 = " << string2 <<endl;

  cout<< "after call with string2 string1 = " << string1 <<endl;

  two_strings(fun("first"), fun("second"));   // output: str1 = first str2 = first. NB: fun pars form stack

  cout<< "\nuse simplified Form0 now" <<endl;

  two_strings(Form0("first"), Form0("second"));   // output: 

  cout<< "\nuse regular ROOT's Form now" <<endl;

  two_strings(Form("first"), Form("second"));   // output: 

  return 0;
}
