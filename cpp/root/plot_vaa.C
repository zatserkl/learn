//DATA 2009.10.23 13:28:24       2424
//DATA 2009.10.23 13:28:56       2412
//DATA 2009.10.23 16:31:15       2418
//DATA 2009.10.23 16:35:14       2412
//DATA 2009.10.23 18:00:24       2418
//DATA 2009.10.28 01:09:46       2410
//DATA 2009.10.29 08:35:22       2416
//DATA 2009.10.29 08:58:59       2410
//DATA 2009.10.30 11:02:15       2416
//DATA 2009.10.30 11:18:09       2409
//DATA 2009.10.30 18:36:00       2416
//DATA 2009.10.30 18:39:11       2410
//DATA 2009.10.30 21:18:10       2416
//DATA 2009.10.30 22:04:13       2410
//DATA 2009.10.31 11:06:19       2416
//DATA 2009.10.31 11:08:23       2409
//DATA 2009.10.31 11:16:24       2415

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdio>
#include <cstring>

#include <TGraph.h>
#include <TCanvas.h>

using std::cout;        using std::endl;

time_t sec1970(const char* date)
{
  // convert date in format like "2009.10.31 11:16:24" to time_t: the number of seconds since Jan 1, 1970

  // C structure tm, all nine members of type int
  //
  // tm_sec	seconds after the minute  0-61*
  // tm_min	minutes after the hour	  0-59
  // tm_hour	hours since midnight	  0-23
  // tm_mday	day of the month	  1-31
  // tm_mon	months since January	  0-11
  // tm_year	years since 1900
  // tm_wday	days since Sunday	  0-6
  // tm_yday	days since January 1	  0-365
  // tm_isdst	Daylight Saving Time flag
  //
  // * tm_sec is generally 0-59. Extra range to accommodate for leap seconds in certain systems.
  // The Daylight Saving Time flag (tm_isdst) is greater than zero if Daylight Saving Time is in effect, zero if Daylight Saving Time is not in effect, and less than zero if the information is not available.  

  int sec;
  int min;
  int hour;
  int day;
  int mon;
  int year;
  std::sscanf(date, "%4d.%2d.%2d %2d:%2d:%2d", &year, &mon, &day, &hour, &min, &sec);

  std::tm timeinfo;
  timeinfo.tm_year = year - 1900;
  timeinfo.tm_mon = mon - 1;
  timeinfo.tm_mday = day;
  timeinfo.tm_hour = hour;
  timeinfo.tm_min = min;
  timeinfo.tm_sec = sec;

  std::time_t t = std::mktime(&timeinfo);
  return t;
}

void plot_vaa(const char* ifname="")
{
  if (std::strlen(ifname) == 0) ifname = __FILE__;
  // cout<< "Reading data from file " << ifname <<endl;

  std::ifstream ifile(ifname);
  if (!ifile) {
    cout<< "File not found: " << ifname <<endl;
    return;
  }

  Float_t time[1000000];
  Float_t value[1000000];

  const std::string pattern = "//DATA ";
  std::string line;

  int nlines = 0;
  while (std::getline(ifile, line))
  {
    if (line.find(pattern, 0) == 0)
    {
      std::stringstream ss;
      ss.str("");
      ss << line.substr(pattern.size());
      std::string yearMonthDay;
      std::string hourMinSec;
      std::string date;
      unsigned val;
      ss >> yearMonthDay >> hourMinSec >> val;
      date = yearMonthDay + " " + hourMinSec;
      std::time_t t = sec1970(date.c_str());

      time[nlines] = t;
      value[nlines] = val;
      ++nlines;

      // cout<< "date = " << date << " t = " << t << " val = " << val <<endl;
    }
  }
  cout<< "Read " << nlines << " data lines from file " << ifname <<endl;

  TGraph* gr = new TGraph(nlines, time, value);
  gr->SetNameTitle("gr","gr");
  gr->SetMarkerStyle(7);
  gr->SetMarkerColor(2);

  new TCanvas;
  gr->Draw("awp");
}
