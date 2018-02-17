/*
~$ locate String\ Theory\ in\ a\ Nutshell\ \(revised edition\)\ ch0-9.pdf | xargs ./enquote 
"/srv/zatserkl/doc/String Theory in a Nutshell (revised edition) ch0-9.pdf /srv/zatserkl/doc/String Theory in a Nutshell (revised edition) ch10-14.pdf"

~$ locate 'String Theory in a Nutshell (revised edition) ch10-14.pdf' | xargs ./enquote | xargs ls -ogh
-rw-r--r-- 1 22M Dec  6  2008 /srv/zatserkl/doc/String Theory in a Nutshell (revised edition) ch10-14.pdf
*/
#include <iostream>
#include <cstdarg>

using std::cout;      using std::endl;

int main(int argc, char *argv[])
{
  cout<< "\"";
  for (int i=1; i<argc; ++i) {
    if (i == 1) cout<< argv[i];
    else cout<< " " << argv[i];
  }
  cout<< "\"" <<endl;
  //cout<< "\"";

  return 0;
}
