// asctime example
#include <ctime>
#include <iostream>
#include <cstdarg>
#include <cstdlib>

using std::cout;    using std::endl;

int main (int argc, char* argv[])
{
  // time_t works as well as std::time_t
  time_t rawtime;                   // time_t: the number of seconds elapsed since 00:00 hours, Jan 1, 1970 UTC
  struct tm* timeinfo;

  // time(&rawtime);                   // Get the current calendar time as a time_t object
  if (argc == 1) {
    time(&rawtime);                   // Get the current calendar time as a time_t object
    cout<< "The current ";
  }
  else {
    rawtime = std::atoi(argv[1]);
  }
  timeinfo = localtime(&rawtime);   // represents time_t value as a local time
  
  cout<< "date/time is: " << asctime(timeinfo) <<endl;
  cout<< "Note that asciitime inserts carrige return (\\n) into the string!" <<endl;
  
  return 0;
}
