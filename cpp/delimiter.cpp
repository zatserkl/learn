#include <iostream>
#include <string>
#include <sstream>

using std::cout;      using std::endl;

std::string tokenize(const std::string& str, const std::string& delimiters)
{
  // replaces any of delimiters in the str by the space symbol

  const char space = ' ';

  std::istringstream ssbuf(str);
  std::ostringstream sstok;
  char c;
  while (ssbuf >> std::noskipws >> c) {
    if (delimiters.find(c) == std::string::npos) sstok << c;
    else sstok << space;
  }
  return sstok.str();
}

main()
{
  std::string date = "2008.10.22 16:56:47";

  std::string delimiters = ".:";

  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;

  std::string date_tokens = tokenize(date, delimiters);
  std::istringstream ss(date_tokens);
  ss >> year >> month >> day >> hour >> minute >> second;

  cout
    << "year = " << year
    << " month = " << month
    << " day = " << day
    << " hour = " << hour
    << " minute = " << minute
    << " second = " << second
  <<endl;
}
