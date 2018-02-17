// http://bytes.com/forum/thread62216.html

#include <map>
#include <string>
#include <iostream>

using std::cout;    using std::endl;

void dual_map_test()
{
  typedef std::map<int, double> t_inner_map;
  typedef std::map<std::string, t_inner_map> t_dual_map;
  t_dual_map amap;
  amap["abc"][12] = 4.3;
  amap["def"][7] = 2.2;
  std::cout << amap["abc"][12] << '\n';
  std::cout << amap["def"][7] << '\n';
}

main()
{
  dual_map_test();
}
