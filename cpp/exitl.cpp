#include <iostream>
#include <cstdlib>

using std::cout;      using std::endl;

std::ostream& mess(std::ostream& os) {
  os << "some message";
  return os;
}

std::ostream& endn(std::ostream& os) {
  os << "\n";
  return os;
}

std::ostream& exitl(std::ostream&) {
  exit(0);
}

bool debug = true;

int main()
{
  std::ostream& (*end)(std::ostream&);
  if (debug) end = std::endl;
  else end = endn;

  // NB: if-then works, but construction with ? does not
  //
  // end = debug? endl: endn;
  // std::ostream& (*end)(std::ostream&) = debug? std::endl: endn;

  cout<< mess << end;

  cout<< "example of exitl" <<endl<<exitl;

  //cout<< "example of exitl" <<exitl;

  cout<< "You will never reach this point!" <<endl;

  return 0;
}
