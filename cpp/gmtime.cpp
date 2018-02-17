#include <ctime>
#include <iostream>

using std::cout;    using std::endl;

#define MST (-7)
#define UTC (0)
#define CCT (+8)

int main ()
{
  time_t rawtime;   // time_t is integer: the number of seconds since Jan 1, 1970
  tm * ptm;         // tm is time structure

  time ( &rawtime );

  /*
  NOTE
  The term Greenwich Mean Time (GMT) was changed to Universal Time Coordinated (UTC) 
  several years ago but GMT is still widely used in the literature and more importantly, 
  it's used in the Standard Library's function names.
  */

  ptm = gmtime ( &rawtime );

  cout<< "Current time around the World:" <<endl;
  cout<< "Phoenix, AZ (U.S.) : " <<  (ptm->tm_hour+MST)%24 << ":" << ptm->tm_min <<endl;
  cout<< "Reykjavik (Iceland) : " << (ptm->tm_hour+UTC)%24 << ":" << ptm->tm_min <<endl;
  cout<< "Beijing (China) : " << (ptm->tm_hour+CCT)%24 << ":" << ptm->tm_min <<endl;

  cout<<endl;
  cout<< "convert GMT time \"2008.10.22 16:56:47\" into time_t" <<endl;

  std::tm gmt;
  gmt.tm_year = 2008 - 1900;
  gmt.tm_mon  = 10 - 1;
  gmt.tm_mday = 22;
  gmt.tm_hour = 16;
  gmt.tm_min  = 56;
  gmt.tm_sec  = 14;

  time_t t_local = mktime(&gmt);  // this will be GMT time interpreted as local
  std::tm* gmt_local = gmtime(&t_local);

  // convert GMT time interpreted as local to GMT
  time_t t_gmt_local = mktime(gmt_local);

  // difference
  time_t dtime = t_gmt_local - t_local;
  cout<< "dtime = " << dtime <<endl;

  // correct gmt time to obtain "real" GMT
  time_t gmt_corr = t_local - dtime;

  std::tm* gmt_real = gmtime(&gmt_corr);

  cout
    << "year = " << gmt_real->tm_year + 1900
    << " month = " << gmt_real->tm_mon + 1
    << " day = " << gmt_real->tm_mday
    << " hour = " << gmt_real->tm_hour
    << " minute = " << gmt_real->tm_min
    << " second = " << gmt_real->tm_sec
  <<endl;

  cout<< "--> Need to be corrected for daylight saving time!" <<endl;
  
  // try diff
  std::tm jan1970;
  gmt.tm_year = 1970 - 1900;
  gmt.tm_mon  = 1 - 1;
  gmt.tm_mday = 1;
  gmt.tm_hour = 0;
  gmt.tm_min  = 0;
  gmt.tm_sec  = 0;
  time_t time0 = mktime(&jan1970);
  cout<< "time0 = " << time0 <<endl;

}
