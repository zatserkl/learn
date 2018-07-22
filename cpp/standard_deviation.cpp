// https://gist.github.com/mattfowler/797af75e59213bd27a1f#file-stdcpp-cpp

/*
clang++ -Wall -std=c++17 standard_deviation.cpp
*/

#include <iostream>
#include <vector>
#include <cmath>        // sqrt. NB: work both: sqrt and std::sqrt
#include <numeric>      // accumulate, inner_product

using std::cout;    using std::endl;

static double standardDeviation(const std::vector<double>& v)
{
  auto sum = std::accumulate(v.begin(), v.end(), 0.0);
  auto mean = sum / v.size();

  auto squareSum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
  return sqrt(squareSum / v.size() - mean * mean);  // NB: std::sqrt is also OK
}

int main()
{
    auto v = std::vector<double>({1., 2., 3., 3., 3., 4., 5.});

    auto sigma = standardDeviation(v);
    std::cout<< "sigma = " << sigma <<std::endl;
}
