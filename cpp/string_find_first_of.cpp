// string::find_first_of
#include <iostream>
#include <string>

using std::cout;    using std::endl;

main()
{
  std::string str("Replace the vowels in this sentence by asterisks.");
  size_t found;

  found = str.find_first_of("aeiou");
  while (found != std::string::npos)
  {
    str[found] = '*';
    found = str.find_first_of("aeiou",found+1);
  }

  cout<< str <<endl;
}
