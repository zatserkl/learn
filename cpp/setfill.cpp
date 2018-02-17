#include <iostream>
#include <iomanip>
#include <cstdio>

using std::cout;      using std::endl;

main()
{
  int year = 2009;
  int month = 8;
  int day = 30;
  int hour = 21;
  int minute = 2;
  int second = 2;

  cout<< "Example from Stroustrup -- does not work as described!" <<endl;
  cout<<  std::setw(4) << std::setfill('#') << '(' << 12 << ")\n";
  cout << '(' << 12 << ")\n";
  cout<<endl;

  //-- setfill acts for whole cout stream
  //-- setw acts on just next insertion operator

  const char ACRed[] = "\e[0;31m";
  const char ACPlain[] = "\e[0m";
  cout<<ACRed;
  cout<< "setfill acts for whole cout stream" <<endl;
  cout<< "setw acts on just next insertion operator" <<endl;
  cout<< ACPlain;
  cout<< std::setfill('0') << std::setw(12) << "month = " << month <<endl<<endl;

  cout<< "default:" <<endl;
  cout<< year <<"."<< month <<"."<< day <<" "<< hour <<":"<< minute <<":"<< second<<endl;

  cout<< "with setfill and setw:" <<endl;
  cout<< std::setfill('0')
    << std::setw(2) << year
    <<"."<< std::setw(2) << month
    <<"."<< std::setw(2) << day
    <<" "<< std::setw(2) << hour
    <<":"<< std::setw(2) << minute
    <<":"<< std::setw(2) << second
    << std::setfill(' ')
  <<endl;

  cout<< "default again:" <<endl;
  cout<< year <<"."<< month <<"."<< day <<" "<< hour <<":"<< minute <<":"<< second<<endl;

  // printf
  // 0 before width means to fill 0 extra space: %02d
  cout<< "\nprintf(\"%d.%02d.%02d %02d:%02d:%02d\\n\", year, month, day, hour, minute, second);" <<endl;
  printf("%d.%02d.%02d %02d:%02d:%02d\n", year, month, day, hour, minute, second);
}
