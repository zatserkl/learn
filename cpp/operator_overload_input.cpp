// see also learn/operator_overload_square_bra.cpp

#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::cout;      using std::endl;

class VectorClass {
public:
  std::vector<std::string> vstring_;
  VectorClass() {}
  VectorClass& operator << (const std::string& parname) {
    vstring_.push_back(parname);
    return *this;
  }
  void Print() const {
    cout<< "VectorClass: vstring_.size() = " << vstring_.size() <<endl;
    for (std::vector<std::string>::const_iterator it=vstring_.begin();
        it!=vstring_.end(); ++it)
    {
      cout<< *it <<endl;
    }
  }
};

class MapClass {
public:
  std::map<int, std::string> mstring_;
  MapClass() {}
  MapClass& operator << (const std::string& parname) {
    mstring_[mstring_.size()] = parname;
    return *this;
  }
  void Print() const {
    cout<< "MapClass: mstring_.size() = " << mstring_.size() <<endl;
    for (std::map<int, std::string>::const_iterator it=mstring_.begin();
        it!=mstring_.end(); ++it)
    {
      cout<< "mstring_[" << it->first << "] = " << it->second <<endl;
    }
  }
  void PrintNonConst() {
    cout<< "MapClass: mstring_.size() = " << mstring_.size() <<endl;
    cout<< "PrintNonConst: output using vector notation" <<endl;
    for (int i=0; i<mstring_.size(); ++i) {
      cout<< "mstring_[" << i << "] = " << mstring_[i] <<endl;
    }
  }
};

class MapIndexClass {
public:
  std::map<std::string, int> mIndexString_;
  MapIndexClass() {}
  MapIndexClass& operator << (const std::string& parname) {
    mIndexString_[parname] = mIndexString_.size() - 1;      // NB: size() - 1
    return *this;
  }
  void Print() const {
    cout<< "MapIndexClass: mIndexString_.size() = " << mIndexString_.size() <<endl;
    for (std::map<std::string, int>::const_iterator it=mIndexString_.begin();
        it!=mIndexString_.end(); ++it)
    {
      cout<< "mIndexString_[" << it->first << "] = " << it->second <<endl;
    }
  }
  int Index(const std::string& parname) const
  {
    std::map<std::string, int>::const_iterator it = mIndexString_.find(parname);
    if (it != mIndexString_.end()) return it->second;
    else {
      cout<< "parname " << parname << " was not found" <<endl;
      return -1;
    }
  }
};

main()
{
  cout<<endl<< "vector" <<endl;
  VectorClass vectorClass;
  vectorClass << "A" << "x0" << "tau1" << "tau2" << "T" << "sigma";
  vectorClass.Print();

  cout<<endl<< "map<int, string>" <<endl;
  MapClass mapClass;
  mapClass << "A" << "x0" << "tau1" << "tau2" << "T" << "sigma";
  mapClass.Print();
  mapClass.PrintNonConst();

  cout<<endl<< "map<string,int>" <<endl;
  MapIndexClass mapIndexClass;
  mapIndexClass << "A" << "x0" << "tau1" << "tau2" << "T" << "sigma";
  mapIndexClass.Print();

  cout<<endl<< "Find indecies" <<endl;
  cout<< "mapIndexClass.Index(\"A\") = " << mapIndexClass.Index("A") <<endl;
  cout<< "mapIndexClass.Index(\"x0\") = " << mapIndexClass.Index("x0") <<endl;
  cout<< "mapIndexClass.Index(\"tau1\") = " << mapIndexClass.Index("tau1") <<endl;
  cout<< "mapIndexClass.Index(\"tau2\") = " << mapIndexClass.Index("tau2") <<endl;
  cout<< "mapIndexClass.Index(\"T\") = " << mapIndexClass.Index("T") <<endl;
  cout<< "mapIndexClass.Index(\"sigma\") = " << mapIndexClass.Index("sigma") <<endl;
  cout<< "mapIndexClass.Index(\"xxx\") = " << mapIndexClass.Index("xxx") <<endl;
}
