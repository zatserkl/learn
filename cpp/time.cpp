#include <iostream>
#include <ctime>

using std::cout;      using std::endl;

main()
{
  int year0   = 2007;
  int month0  = 1;
  int day0    = 1;
  int hour0   = 0;
  int min0    = 0;
  int sec0    = 0;

  int year1   = 2007;
  int month1  = 12;
  int day1    = 5;
  int hour1   = 5;
  int min1    = 44;
  int sec1    = 23;

  int year2   = 2007;
  int month2  = 12;
  int day2    = 5;
  int hour2   = 6;
  int min2    = 58;
  int sec2    = 16;

  //
  // NB: 
  // std::tm timeinfo0;
  // correct as well as
  // struct std::tm timeinfo0;
  //
  struct std::tm timeinfo0;
  struct std::tm timeinfo1;
  struct std::tm timeinfo2;
  
  timeinfo0.tm_year  = year0 - 1900;
  timeinfo0.tm_mon   = month0 - 1;
  timeinfo0.tm_mday  = day0;
  timeinfo0.tm_hour  = hour0;
  timeinfo0.tm_min   = min0;
  timeinfo0.tm_sec   = sec0;
  
  timeinfo1.tm_year  = year1 - 1900;
  timeinfo1.tm_mday  = day1 - 1;
  timeinfo1.tm_mon   = month1;
  timeinfo1.tm_hour  = hour1;
  timeinfo1.tm_min   = min1;
  timeinfo1.tm_sec   = sec1;

  timeinfo2.tm_year  = year2 - 1900;
  timeinfo2.tm_mday  = day2 - 1;
  timeinfo2.tm_mon   = month2;
  timeinfo2.tm_hour  = hour2;
  timeinfo2.tm_min   = min2;
  timeinfo2.tm_sec   = sec2;
  
  cout<< "before mktime: timeinfo1.tm_wday = " << timeinfo1.tm_wday <<endl;
  
  std::time_t abstime0 = std::mktime(&timeinfo0);
  std::time_t abstime1 = std::mktime(&timeinfo1);
  std::time_t abstime2 = std::mktime(&timeinfo2);
  
  cout<< "after  mktime: timeinfo1.tm_wday = " << timeinfo1.tm_wday <<endl;

  cout<< "abstime1-abstime0 = " << abstime1-abstime0 << " abstime2-abstime0 = " << abstime2-abstime0 << " diff = " << abstime2 - abstime1 <<endl;
}
