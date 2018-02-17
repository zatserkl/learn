/*  *** lines 2-5 are data for this program ***
    John|83|52.2
    swimming|Jefferson
    Jane|26|10.09
    sprinting|San Marin
*/

// based on http://augustcouncil.com/~tgibson/tutorial/iotips.html

#include <iostream>
#include <fstream>
#include <string>

using std::cout;      using std::endl;

main()
{
  std::ifstream ifile(__FILE__);
  if (!ifile) {
    cout<< "File not found: " << __FILE__ <<endl;
    return 0;
  }
  std::string name;
  while(!std::getline(ifile, name, '|').eof())
  {
    //Athlete* ap;
    std::string jersey_number;
    std::string best_time;
    std::string sport;
    std::string high_school;
    std::getline(ifile, jersey_number, '|'); //read thru pipe
    std::getline(ifile, best_time);          //read thru newline
    std::getline(ifile, sport, '|');         //read thru pipe
    std::getline(ifile, high_school);        //read thru newline
    // ap = new Athlete(name, strtod(number.c_str()), strtof(best_time.c_str()), sport, high_school);
    //do something with ap
    cout<< "jersey_number " << jersey_number << " best_time " << best_time << " sport " << sport << " high_school " << high_school <<endl;
  }
}
