/*
The same question as in rdbuf.cpp

http://ubuntuforums.org/showthread.php?t=67867

Q: For a program I'm writing, I need to copy a file character for character into a vector of type char. That includes spaces and endlines. Thing is I kinda don't know how to do it.

A: The most trivial way would be to do something like that.
   Really, the file >> std::noskipws; is the critical operation here: it turns off whitespace skipping on formatted input streams. Using copy is just convient for slurping a whole file.
*/

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>

int
main()
{
  typedef std::istream_iterator<char> istream_iterator;
  std::ifstream file("stdcopy.cpp");
  std::vector<char> input;

	// clears the 'skipws' format flag for the stream 'file' using manipulator function
	//
	// ios_base& noskipws ( ios_base& some_stream );
	//
  file >> std::noskipws;
	//
	// the same using fuctional form
	//
	// std::noskipws(file);

  std::copy(istream_iterator(file), istream_iterator(),
            std::back_inserter(input));
	
	for (std::vector<char>::const_iterator i_char=input.begin(); i_char!=input.end(); ++i_char)
	{
		std::cout<< *i_char;
	}
}
