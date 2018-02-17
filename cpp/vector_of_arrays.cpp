#include <iostream>
#include <vector>

using std::cout;      using std::endl;

main()
{
  //typedef float[8] array8;
  // std::vector<float[8]> vfloat8;
  std::vector<float*> vfloat8;

  float a[8];
  for (int i=0; i<8; ++i) a[i] = i;
  vfloat8.push_back(a);

  for (int i=0; i<8; ++i) a[i] = 10*i;
  vfloat8.push_back(a);

  for (int i=0; i<8; ++i) a[i] = 100*i;
  vfloat8.push_back(a);

  for (std::vector<float*>::const_iterator it=vfloat8.begin(); it!=vfloat8.end(); ++it) {
    for (int i=0; i<8; ++i) {
      const float* ap = *it;
      cout<< "   " << ap[i] <<endl;
      // cout<< "   " << (*it)[i] <<endl;
    }
  }
}

/*
 * compiled but result is wrong!
 * see discussion in http://bytes.com/forum/thread60075.html
   0
   100
   200
   300
   400
   500
   600
   700
   0
   100
   200
   300
   400
   500
   600
   700
   0
   100
   200
   300
   400
   500
   600
   700
*/
