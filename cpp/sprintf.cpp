#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>

using std::cout;      using std::endl;

typedef int Int_t;

std::string makedate_c(Int_t year, Int_t mon, Int_t day, Int_t hour, Int_t min, Int_t sec) {
  // strict data format: "2008.10.31 13:22:38" 
  char str[20];
  sprintf(str, "%d.%02d.%02d %02d:%02d:%02d", year,mon,day, hour,min,sec);
  return std::string(str);
}

std::string makedate_cpp(Int_t year, Int_t mon, Int_t day, Int_t hour, Int_t min, Int_t sec) {
  // strict data format: "2008.10.31 13:22:38" 
  std::stringstream ss;
  ss.str("");
  //ss.setw(2);
  //std::cin.noskipws();
  //ss << std::setfill('0') << year <<"."<< std::setw(2) << mon <<"."<< std::setw(2) << day <<" "<< std::setw(2) << hour <<":"<< std::setw(2) << min <<":"<< std::setw(2) << sec <<endl;
  ss << std::setfill('0') << year <<"."<< std::setw(2) << mon <<"."<< std::setw(2) << day <<" "<< std::setw(2) << hour <<":"<< std::setw(2) << min <<":"<< std::setw(2) << sec <<endl;
  return ss.str();
}

main()
{
  // int year = 2008;
  // int mon = 10;
  // int day = 31;
  // int hour = 13;
  // int min = 22;
  // int sec = 38;
  int year = 2008;
  int mon = 1;
  int day = 3;
  int hour = 4;
  int min = 2;
  int sec = 8;

  //std::string date = makedate_c(year,mon,day, hour,min,sec);
  cout<< "date = " << makedate_c(year,mon,day, hour,min,sec) <<endl;

  cout<< "date = " << makedate_cpp(year,mon,day, hour,min,sec) <<endl;
}
