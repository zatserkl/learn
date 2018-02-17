#include <iostream>
#include <cstdio>
#include <string>

using std::cout;      using std::endl;

typedef int Int_t;

main()
{
  // strict data format: "2008.10.31 13:22:38" 
  std::string date = "2008.10.31 13:22:38";
  cout<< "date = " << date <<endl;

  Int_t year, month, day, hour, minute, second;
  sscanf(date.c_str(), "%4d.%2d.%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minute, &second);
  
  cout<< "year=" << year << " month=" << month << " day=" << day << " hour=" << hour << " minute=" << minute << " second=" << second <<endl;
}
