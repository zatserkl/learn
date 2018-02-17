#include <iostream>
#include <vector>

// about vector of arrays see e.g. see discussion in http://bytes.com/forum/thread60075.html

using std::cout;      using std::endl;

// further test of this class will be in other source file
template <class T>
class Varray {
  int dim_;
  std::vector<T> v_;
public:
  Varray(unsigned dim) {
    v_.resize(dim);
    //for
  }
  void Resize(unsigned dim) {
    v_.resize(dim);
  }
};

main()
{
  std::vector<std::vector<double> > calibs;

  std::vector<double> v;
  v.resize(8);
  //-- for (int i=0; i<8; ++i) v.push_back(0); 

  // v.clear();
  // for (int i=0; i<8; ++i) v.push_back(i);
  for (int i=0; i<8; ++i) v[i] = i;
  calibs.push_back(v);

  v.clear();
  for (int i=0; i<8; ++i) v.push_back(10*i);
  calibs.push_back(v);
  
  v.clear();
  for (int i=0; i<8; ++i) v.push_back(100*i);
  calibs.push_back(v);

  for (std::vector<std::vector<double> >::const_iterator it=calibs.begin(); it!=calibs.end(); ++it) {
    for (int i=0; i<8; ++i) {
      cout<< it->at(i) << "   ";
    }
    cout<<endl;
  }

  Varray<float> vfloat(8);

}
