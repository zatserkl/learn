#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

using std::cout;      using std::endl;

main()
{
	std::string line = "Time: Fri Aug  7 21:31:44 2009 : Baseline Correction for FED 0x13000000, Channel 1 has Mean=10.8 and StdDev=1.32665";

	float mean;

	const std::string pattern = "Mean=";
	const size_t len = pattern.size();

	size_t pos = line.rfind(pattern) + len;
	cout<< line.substr(pos) <<endl;
	sscanf(line.substr(pos).c_str(), "%f", &mean);

	cout<< "mean = " << mean <<endl;
}
