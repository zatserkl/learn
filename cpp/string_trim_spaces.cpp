#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

#include <string> 
#include <iostream>
using std::cout;    using std::endl;

/*
http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

They are fairly self explanatory and work very well.

EDIT: btw, I have std::ptr_fun in there to help disambiguate std::isspace
because there is actually a second definition which supports locales.
This could have been a cast just the same, but I tend to like this better.
*/

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

int main()
{
  std::string str = "   this   is a string with spaces   ";
  cout<< "before trim: '" << str << "'" <<endl;

  ltrim(str);
  cout<< "after trim of the start spaces: '" << str << "'" <<endl;

  // simple way
  str = "   this   is a string with spaces   ";
  while (std::isspace(str[0])) str.erase(0,1);
  cout<< "after trim of the start spaces in the simple way: '" << str << "'" <<endl;
}
