#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using std::cout;      using std::endl;

//
//  The stringstream may go to the eof state and become blocked for the next loop iteration.
//  The best is to create the std::stringstream object in every loop iteration.
//

void write_file(const char* fname)
{
  cout<< "Write down a text file " << fname <<endl;

  std::ofstream file(fname);

  file << "test file" <<endl;
  file << endl;

  file << "run 1" << endl;
  file << endl;

  file << "#" << endl;
  file << "# Sep2014" << endl;
  file << "#" << endl;
  file << endl;
  file << "run 30" << endl;

  file.close();
}

void read_file_good(const char* fname)
{
  //
  //  The stringstream may go to the eof state and become blocked for the next loop iteration.
  //  The best is to create the std::stringstream object in every loop iteration.
  //

  cout<< "read the file " << fname <<endl;

  std::string line;
  std::string word1, word2;
  int run = 0;

  std::ifstream ifile(fname);
  if (!ifile) {
    cout<< "Could not find file " << fname <<endl;
    return;
  }
  else cout<< "reading file " << fname <<endl;

  while (std::getline(ifile, line))
  {
    cout<< "line: " << line <<endl;

    if (line.size() == 0) continue;

    std::stringstream ss(line);             // construct std::stringstream for each loop iteration

    ss >> word1;
    cout<< "word1 = " << word1 <<endl;
    if (word1 == "run") {
      // ss >> word2;
      // cout<< "word2 = " << word2 <<endl;
      ss >> run;
      cout<< "run = " << run <<endl;
    }
  }
}

void read_file(const char* fname)
{
  //
  //  The stringstream may go to the eof state and become blocked for the next loop iteration.
  //  The best is to create the std::stringstream object in every loop iteration.
  //

  cout<< "read the file " << fname <<endl;

  std::string line;
  std::string word1, word2;
  int run = 0;

  std::ifstream ifile(fname);
  if (!ifile) {
    cout<< "Could not find file " << fname <<endl;
    return;
  }
  else cout<< "reading file " << fname <<endl;

  std::stringstream ss;                         // NB: global stringstream object

  while (std::getline(ifile, line))
  {
    cout<< "line: " << line <<endl;

    if (line.size() == 0) continue;

    //--NB-- ss.clear();            //-- ss.clear() before use solves the problem, actually

    if (!ss.good()) {
      cout<< "--> ss is not good at this point!" <<endl;
      cout<< "    before the ss.str(line): ss.good() = " << std::boolalpha << ss.good()
        << ":\t ss.eof() = " << ss.eof()
        << ":\t ss.fail() = " << ss.fail()
        << ":\t ss.bad() = " << ss.bad()
      <<endl;
    }

    ss.str(line);          // will not work if ss is blocked by previous eof

    ss >> word1;
    if (ss.good() == false) {
      cout<< "    ss.good() = " << std::boolalpha << ss.good()
        << ":\t ss.eof() = " << ss.eof()
        << ":\t ss.fail() = " << ss.fail()
        << ":\t ss.bad() = " << ss.bad()
      <<endl;
      cout<< "    call ss.clear()" <<endl;
      ss.clear();
      cout<< "    after ss.clear(): ss.good() = " << std::boolalpha << ss.good()
        << ":\t ss.eof() = " << ss.eof()
        << ":\t ss.fail() = " << ss.fail()
        << ":\t ss.bad() = " << ss.bad()
      <<endl;
    }

    cout<< "word1 = " << word1 <<endl;
    if (word1 == "run") {
      // ss >> word2;
      // cout<< "word2 = " << word2 <<endl;
      ss >> run;
      cout<< "run = " << run <<endl;
    }
  }
}

int main(int argc, char *argv[])
{
  //
  //  The stringstream goes to the eof state and became blocked for next loop iteration.
  //  The best is to create the std::stringstream object in every loop iteration.
  //

  const char* fname = "getline_loop.dat";

  if (argc > 1) fname = argv[1];
  cout<< "fname = " << fname <<endl;

  write_file(fname);
  // read_file_good(fname);
  read_file(fname);

  return 0;
}
