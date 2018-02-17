/* strtok example */
#include <string>
#include <cstring>
#include <iostream>

using std::cout;        using std::endl;

int main ()
{
  // std::string str = "- This, a sample string.";
  std::string str = "2008.10.22 16:56:47";

  char* buf = new char[str.size()+1];
  memcpy(buf, str.data(), str.size()+1);

  std::string delimiters = " ,.:-";
  char* ptr;

  cout<< "string before tokenize: \"" << buf << "\"" <<endl;

  // cout<< "Splitting string " << buf << " into tokens:" <<endl;
  ptr = strtok (buf, delimiters.c_str());
  while (ptr)
  {
    cout<< ptr <<endl;
    ptr = strtok (0, delimiters.c_str());
  }

  cout<< "string after  tokenize: \"" << buf << "\"" <<endl;

  delete[] buf;
}
