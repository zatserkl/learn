#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <cstring>
#include <cstdio>

using std::cout;    using std::endl;

int string_nwords(std::string str)
{
  std::istringstream ss(str);   // use ss(str+"\n") in ROOT
  size_t nwords = 0;
  while (ss >> str) ++nwords;
  return nwords;
}

int string_nwords_iterator(std::string str)
{
  std::istringstream ss(str);
  size_t nwords = 0;
  for (std::istream_iterator<std::string> it(ss), end; it!=end; ++it) {    // NB: iterator end isn't initialized yet
    ++nwords;
    cout<< nwords << "\t " << *it <<endl;
  }
  return nwords;
}

int string_nwords_strtok(std::string str, std::string delimiters=" ,;:-")
{
  char* buf = new char[str.size()+1];
  memcpy(buf, str.data(), str.size()+1);

  int nwords = 0;
  char* ptr = strtok (buf, delimiters.c_str());
  while (ptr)
  {
    ++nwords;
    cout<< ptr <<endl;
    ptr = strtok (0, delimiters.c_str());
  }
  return nwords;
}

// pure C version
int cstring_nwords_strtok(const char* str, const char* delimiters=" ,;:-")
{
  char* buf = new char[strlen(str)+1];
  memcpy(buf, str, strlen(str)+1);

  int nwords = 0;
  char* ptr = strtok (buf, delimiters);
  while (ptr)
  {
    ++nwords;
    cout<< ptr <<endl;
    ptr = strtok (0, delimiters);
  }
  delete[] buf;
  return nwords;
}

// sscanf version
int string_nwords(const char* str, const char* delimiters=" ,;:-")
{
  char buf[1025];
  buf[0] = '\0';
  int nwords = 0;
  // while (sscanf(str, "%s", buf)) {
  //   ++nwords;
  //   cout<< buf <<endl;
  // }
  nwords = sscanf(str, "%s%s%s%s%s%s", buf, buf, buf, buf, buf, buf);
  cout<< "buf = " << buf <<endl;
  return nwords;
}

main()
{
  std::string str = "portcardName_ = FPix_BpO_D2_PRT4 dcuId_ = 0 fecBoardId_ = 18 mfecId_ = 7 ccuId_ = 123 ccuChannelId_ = 17";

  cout<< "string\n" << str << "\ncontains " << string_nwords(str) << " words" <<endl;
  cout<< "\n--- Using C strtok ---\n" <<endl;
  cout<< "Using strtok: the number of words is " << string_nwords_strtok(str.c_str()) <<endl;

  std::string str1 = "10 100";
  cout<< "\nsscanf version: str1 = " << str1 <<endl;
  cout<< "\nsscanf version: nwords = " << string_nwords(str1.c_str()) <<endl;

  cout<< "\nSpecial tests with string which contains spaces only" <<endl;

  str = "   ";

  cout<< "string\n" << str << "\ncontains " << string_nwords(str) << " words" <<endl;
  cout<< "\n--- Using C strtok ---\n" <<endl;
  cout<< "Using strtok: the number of words is " << string_nwords_strtok(str.c_str()) <<endl;
}
