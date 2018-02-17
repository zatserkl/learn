/* getchar example : typewriter */
#include <iostream>
#include <cstdio>
#include <string>

using std::cin;    using std::cout;    using std::endl;

int main ()
{
  char c = '\n';
  cout<< "value of (unsigned) \\n is " << (unsigned) c <<endl;
  cout<< "Enter char ";
  cin.get(c);
  cout<< "c = " << (unsigned) c <<endl;
  return 0;

  puts ("Enter text. Include a dot ('.') in a sentence to exit:");
  do {
    c=getchar();
    // cin >> c;
    cout<< "c = " << (unsigned) c <<endl;
    // putchar (c);
  } while (c != '.');

  //-- the best way is to use std::getline(cin, string) like in utils.C png
  cout<< "File exists: xxxxxx" <<endl;
  cout<< "Enter <CR> to overwrite, any other key to quit: ";
  std::string str;
  std::getline(cin, str);	 // read complete line to avoid problems with the next call
  if (str.size() > 0) {
    cout<< "*** quit without saving" <<endl;
    return 0;
  }

  return 0;
}
