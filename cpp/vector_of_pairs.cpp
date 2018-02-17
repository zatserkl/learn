// from http://bytes.com/forum/thread60075.html
//
// see discussion about vector of arrays there

#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

typedef std::pair<int, int> coord_t;
typedef std::vector<coord_t> coord_list_t;

std::ostream& operator<<(std::ostream& os,
const coord_t& coord)
{
return os << coord.first << ", " << coord.second;
}

std::ostream& operator<<(std::ostream& os,
const coord_list_t& lst)
{
for(coord_list_t::size_type i = 0; i != lst.size(); ++i)
os << lst[i] << '\n';

return os;
}

int main()
{
coord_list_t coordVector;
coordVector.push_back(coord_t( 0, 0));
coordVector.push_back(coord_t(42, 25));
coordVector.push_back(coord_t(18, 69));

std::cout << coordVector << '\n';
return 0;
}
