#include <vector>
#include <iostream>

using namespace std;

void vector2dim()
{
  int nstrips = 5;
  int nevents = 3;
  
  std::vector<int>* vevent = new std::vector<int>;  // temporary vector of strips for given event
  
  std::vector< std::vector<int> > vEventModule;
  
  for (int ievent=0; ievent<nevents; ++ievent) {
    // prepare "event" vector
    vevent->clear();
    for (int istrip=0; istrip<nstrips; ++istrip) {
      int strip = (ievent+1)*10 + (istrip+1);
      vevent->push_back(strip);
    }
    vEventModule.push_back(*vevent);
  }
  
  cout<< "print all vEventModule[ievent][istrip]" <<endl;
  for (int ievent=0; ievent<nevents; ++ievent) {
    for (int istrip=0; istrip<nstrips; ++istrip) {
      cout<< "v[" << ievent << "][" << istrip << "] = " << vEventModule[ievent][istrip] << "   ";
    }
    cout<<endl;
  }

  // test of vi settings
  if (true) {
  	cout<< "test" <<endl;
  }
}

// #ifndef CINT
main() {vector2dim();}
// #endif
