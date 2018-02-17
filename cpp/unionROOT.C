/*
compiled w/o problem using
g++ -Wall -c unionROOT.C

ACLiC has problems when union is declared in the global scope.
Declaration inside the function causes no problem.
*/


#include <iostream>

using std::cout;      using std::endl;

typedef int Int_t;
typedef unsigned int UInt_t;
typedef char Char_t;
typedef unsigned short UShort_t;
typedef float Float_t;

struct DRS4eventCompiles {
   union Event {
      struct Field {
         char header[4];
         UInt_t number;
         UShort_t year;
         UShort_t month;
         UShort_t day;
         UShort_t hour;
         UShort_t minute;
         UShort_t second;
         UShort_t millisecond;
         UShort_t reserved;
         Float_t t[1024];
      } field;
      char buffer[24 + 4*1024];
   };
};

struct DRS4Event {
   union EventTime {
      struct Field {
         Char_t header[4];
         UInt_t number;
         UShort_t year;
         UShort_t month;
         UShort_t day;
         UShort_t hour;
         UShort_t minute;
         UShort_t second;
         UShort_t millisecond;
         UShort_t reserved;
         Float_t t[1024];
      } field;
      char buffer[4 + 1*4 + 2*8 + 1024*4];
      EventTime(): buffer() {
         for (unsigned ipoint=0; ipoint<sizeof(buffer); ++ipoint) buffer[ipoint] = 0;
      }
      bool Read(std::istream ifile) {
         // file size
         Long64_t curr = ifile.tellg();
         ifile.seekg(0, std::ios::end);
         Long64_t ifsize = ifile.tellg();
         ifile.seekg(curr);
      }
   } time;
   union Channel {
      struct Field {
         Char_t header[4];
         UShort_t voltage;
      } field;
      Char_t buffer[4 + 1024*2];
      Channel() {
         for (unsigned ipoint=0; ipoint<sizeof(buffer); ++ipoint) buffer[ipoint] = 0;
      }
   } channel[4];
};

//
// anonimous union cannot be declared in global scope in ROOT
//
/// union DRS4Event_global_scope {
///    char buffer[24 + 4*1024];
///    struct Fields{
///       char header[4];
///       UInt_t number;
///       UShort_t year;
///       UShort_t month;
///       UShort_t day;
///       UShort_t hour;
///       UShort_t minute;
///       UShort_t second;
///       UShort_t millisecond;
///       UShort_t reserved;
///       Float_t t[1024];
///    };
/// };

// try to declare inside the class Event

// struct DRS4EventChan {
//    union Event {
//       struct {
//          Char_t header[4];
//          UInt_t number;
//          UShort_t year;
//          UShort_t month;
//          UShort_t day;
//          UShort_t hour;
//          UShort_t minute;
//          UShort_t second;
//          UShort_t millisecond;
//          UShort_t reserved;
//          Float_t t[1024];
//       };
//       Char_t buffer[24 + 4*1024];
//    };
//    union Chan {
//       struct {
//          Char_t header[4];
//          UShort_t voltage[1024];
//       };
//       Char_t buffer[4 + 2*1024];
//    };
// };


/// // unnamed struct inside the union
/// union Par_global_scope {
///    int a[10];
///    struct {
///       int a1;
///       int a2;
///       int a3;
///    };          // NB: anonymous union. Does not supported by CINT
/// };

//main()
void unionROOT()
{
   DRS4Event event;

   event.time.buffer[0] = 'E';
   event.time.buffer[1] = 'H';
   event.time.buffer[2] = 'D';
   event.time.buffer[3] = 'R';

   for (int ipoint=0; ipoint<4; ++ipoint) {
      // cout<< ipoint << "\t " << event.time.t[ipoint] <<endl;
      cout<< ipoint << "\t " << event.time.buffer[ipoint] <<endl;
      cout<< ipoint << "\t " << (unsigned) (unsigned char) event.time.buffer[ipoint] <<endl;
      cout<< ipoint << "\t " << event.time.field.t[ipoint] <<endl;
   }

   DRS4Event::Channel channel;
   cout<< "channel.field.header[0] = " << (unsigned) (unsigned char) channel.field.header[0] <<endl;
   //////////////////////////////////////////////////////////////////

   union DRS4Event_inside_function {
      char buffer[24 + 4*1024];
      struct {
         char header[4];
         UInt_t number;
         UShort_t year;
         UShort_t month;
         UShort_t day;
         UShort_t hour;
         UShort_t minute;
         UShort_t second;
         UShort_t millisecond;
         UShort_t reserved;
         Float_t t[1024];
      };
   };

  // unnamed struct inside the union
  union Par {
    int a[10];
    struct {
      int a1;
      int a2;
      int a3;
    };          // NB: anonymous union. Does not supported by CINT
  };

  Par par;
  par.a1 = 1;
  par.a2 = 2;
  par.a3 = 3;
  for (int i=0; i<3; ++i) cout<< "par.a[" << i << "] = " << par.a[i] <<endl;

  // named struct inside the union

  union ParObject {
    int a[10];
    struct {
      int a1;
      int a2;
      int a3;
    } object;
  };

  ParObject parObject;
  parObject.object.a1 = 1;
  parObject.object.a2 = 2;
  parObject.object.a3 = 3;
  for (int i=0; i<3; ++i) cout<< "par.a[" << i << "] = " << par.a[i] <<endl;
}
