#include <iostream>

using std::cout;    using std::endl;

enum Color {
  red,
  blue,
  green
};

void print_red(Color color)
{
  if (color == red) cout<< "--> red" <<endl;
}

main()
{
  Color color;
  color = red;

  print_red(color);
}
