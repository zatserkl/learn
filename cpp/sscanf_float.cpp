#include <iostream>
#include <string>
#include <cstdio>

using std::cout;      using std::endl;

main()
{
	std::string str1 = "Mean=10.5e-1";	// NB: format %f works for scientific notation too
	std::string str2 = "Mean=10";				//-- no decimal point: OK

	float mean1 = 0;
	float mean2 = 0;

	sscanf(str1.c_str(), "Mean=%f", &mean1);
	sscanf(str2.c_str(), "Mean=%f", &mean2);

	cout<< "mean1 = " << mean1 << " mean2 = " << mean2 <<endl;

	// NB: to read double the format need modifier 'l': %lf instead of %l
	// See e.g. http://www.cplusplus.com/reference/clibrary/cstdio/sscanf/

	double mean_double1 = 0;
	double mean_double2 = 0;

	sscanf(str1.c_str(), "Mean=%lf", &mean_double1);
	sscanf(str2.c_str(), "Mean=%lf", &mean_double2);

	cout<< "mean_double1 = " << mean_double1 << " mean_double2 = " << mean_double2 <<endl;
}
