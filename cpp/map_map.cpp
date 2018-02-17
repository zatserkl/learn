#include <iostream>
#include <map>
#include <string>

using std::cout;      using std::endl;

typedef std::map<std::string, std::map<std::string, double> > map_str_map_str_double;

map_str_map_str_double& get_mapmap()
{
  std::string alias1 = "alias1";
  std::string alias2 = "alias2";

  std::string date1 = "2008.11.08 22:47:56";
  std::string date2 = "2008.11.09 23:48:57";

  double value_alias1_date1 = 10;
  double value_alias1_date2 = 20;
  double value_alias2_date1 = 100;
  double value_alias2_date2 = 200;

  map_str_map_str_double *mapmap = new map_str_map_str_double;

  (*mapmap)[alias1][date1] = value_alias1_date1;
  (*mapmap)[alias1][date2] = value_alias1_date2;
  (*mapmap)[alias2][date1] = value_alias2_date1;
  (*mapmap)[alias2][date2] = value_alias2_date2;

  return *mapmap;
}

main()
{
  map_str_map_str_double& mapmap = get_mapmap();
  for (map_str_map_str_double::const_iterator i_mapmap=mapmap.begin(); i_mapmap!=mapmap.end(); ++i_mapmap)
  {
    for (std::map<std::string, double>::const_iterator i_map=i_mapmap->second.begin(); i_map!=i_mapmap->second.end(); ++i_map)
    {
      cout<< "alias " << i_mapmap->first << " date " << i_map->first << " value " << i_map->second <<endl;
    }
  }
}
