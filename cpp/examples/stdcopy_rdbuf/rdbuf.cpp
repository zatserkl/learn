/*
The same question as in stdcopy.cpp

http://ubuntuforums.org/showthread.php?t=67867

Q: For a program I'm writing, I need to copy a file character for character into a vector of type char. That includes spaces and endlines. Thing is I kinda don't know how to do it.

A: The most trivial way would be to do something like that.
   Really, the file >> std::noskipws; is the critical operation here: it turns off whitespace skipping on formatted input streams. Using copy is just convient for slurping a whole file.


An alternative is to use the streaming of the file buffer directly using the rdbuf. This way goes through a temporary string, and constructs the vector from that:
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cout << "usage: " << argv[0] << " <filename>\n";
    return 2;
  }

  std::ifstream fin(argv[1]);
  if (fin) {
    std::stringstream ss;
    // this copies the entire contents of the file into the string stream
    ss << fin.rdbuf();
    // get the string out of the string stream
    std::string contents = ss.str();
    std::cout << contents;
    // construct the vector from the string.
    std::vector<char> buff(contents.begin(), contents.end());
  }
  else {
    std::cout << "Couldn't open " << argv[1] << "\n";
    return 1;
  }
  return 0;
}
