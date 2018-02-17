#include <ctime>
#include <clocale>
#include <iostream>

using std::cout;        using std::endl;

int main ()
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];

  struct lconv * lc;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  int twice=0;

  do {
    cout<< "Locale is: " << setlocale(LC_ALL,NULL) <<endl;

    strftime (buffer,80,"%c",timeinfo);
    cout<< "Date is: " << buffer <<endl;

    lc = localeconv();
    cout<< "Currency symbol is: " << lc->currency_symbol << "\n-\n" <<endl;

    setlocale (LC_ALL,"");
  } while (!twice++);
  
  return 0;
}
