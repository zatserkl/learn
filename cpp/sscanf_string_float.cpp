/*
learn$ root -l
*-- Local rootlogon
// .L sscanf_string_float.cpp+
Info in <TUnixSystem::ACLiC>: creating shared library /home/zatserkl/learn/./sscanf_string_float_cpp.so
// read_string()
mean = 1.05
"Sample Interval"	5E-12	s	-2.06950000e-008	-7.62939517e-010
SampleInterval = 5e-12
0	 -2.0695e-08	 -7.6294e-10
*/

#include <iostream>
#include <string>
#include <cstdio>

using std::cout;      using std::endl;

void read_string()
{
	std::string str = "Mean    =     10.5e-1";	// NB: format %f works for scientific notation too

	float mean = 0;

	sscanf(str.c_str(), "Mean = %f", &mean);

	cout<< "mean = " << mean <<endl;

  str = "\"Sample Interval\"	5E-12	s	-2.06950000e-008	-7.62939517e-010";
  cout<< str <<endl;

  double SampleInterval = -1.;
  double x[1000], y[1000];
  int np = 0;

  sscanf(str.c_str(), "\"Sample Interval\"	%lf	s	%lf %lf", &SampleInterval, &x[np], &y[np]);
  np++;
  cout<< "SampleInterval = " << SampleInterval <<endl;
  for (int i=0; i<np; ++i) cout<< i <<"\t "<< x[i] <<"\t "<< y[i] <<endl;
}

int main()
{
  read_string();

	// // NB: to read double the format need modifier 'l': %lf instead of %l
	// // See e.g. http://www.cplusplus.com/reference/clibrary/cstdio/sscanf/

	// std::string str1 = "Mean=10.5e-1";	// NB: format %f works for scientific notation too
	// std::string str2 = "Mean=10";				//-- no decimal point: OK

	// double mean_double1 = 0;
	// double mean_double2 = 0;

	// sscanf(str1.c_str(), "Mean=%lf", &mean_double1);
	// sscanf(str2.c_str(), "Mean=%lf", &mean_double2);

	// cout<< "mean_double1 = " << mean_double1 << " mean_double2 = " << mean_double2 <<endl;

	return 0;
}
