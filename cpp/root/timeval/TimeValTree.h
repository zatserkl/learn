#include <TObject.h>
#include <TTimeStamp.h>

#ifndef TimeValTree_h
#define TimeValTree_h

class TimeValTree: public TObject {
public:
  Int_t year;
  Int_t mon;
  Int_t day;
  Int_t hour;
  Int_t min;
  Int_t sec;
  Int_t time;
  Float_t val;
  TimeValTree(): TObject()
                 , year(0)
                 , mon(0)
                 , day(0)
                 , hour(0)
                 , min(0)
                 , sec(0)
                 , time(0)
                 , val(0)
  {}
  void Set(Int_t year1, Int_t mon1, Int_t day1, Int_t hour1, Int_t min1, Int_t sec1, Float_t val1)
  {
    year = year1;
    mon = mon1;
    day = day1;
    hour = hour1;
    min = min1;
    sec = sec1;
    val = val1;
    TTimeStamp ts;
    Int_t nsec = 0;
    Bool_t isUTC = kTRUE;
    Int_t secOffset = 0;    // provides method for adjusting for alternative timezones
    ts.Set(year, mon, day, hour, min, sec, nsec, isUTC, secOffset);
    time = ts.GetSec();
  }
  ClassDef(TimeValTree, 2)
};

#endif // TimeValTree_h
