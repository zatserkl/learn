/* asctime example */
#include <iostream>
#include <ctime>

using std::cout;      using std::endl;      using std::cin;

int main ()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  
  timeinfo = localtime ( &rawtime );
  cout<< "The current date/time (rawtime = " << rawtime << ") is: " << asctime (timeinfo) <<endl;
  
  //cout<<endl;

  int year   = 2008;
  int mon    = 1;
  int day    = 15;
  int hour   = 0;
  int min    = 0;
  int sec    = 0;

  struct std::tm timeinfo0;
  timeinfo0.tm_year  = year - 1900;
  timeinfo0.tm_mon   = mon - 1;
  timeinfo0.tm_mday  = day;
  timeinfo0.tm_hour  = hour;
  timeinfo0.tm_min   = min;
  timeinfo0.tm_sec   = sec;
  std::time_t time0 = std::mktime(&timeinfo0);
  
  cout<<endl<< "time0 for Jan 15, 2008 is " << time0 <<endl;
  
  cout<< "Enter seconds from Jan 15, 2008" <<endl;
  double rawtime_double;
  cin >> rawtime_double;
  rawtime = static_cast<std::time_t>(rawtime_double);
  
  rawtime += time0;
  
  cout<< "Your date is " << asctime(localtime(&rawtime));
  
  return 0;
}
