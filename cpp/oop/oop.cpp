#include <iostream>
#include <vector>

class BaseNumber {
public:
    BaseNumber() {
        std::cout << "-- Constructor BaseNumber" << std::endl;
    }
    virtual void Show() {                                       // virtual method
        std::cout << "BaseNumber::Show" << std::endl;
    }
};

class RealNumber: public BaseNumber {
public:
    int re;

    RealNumber(int re_0): BaseNumber(), re(re_0) {
        std::cout << "-- Constructor RealNumber" << std::endl;
    }
    void Show() {
        std::cout << "RealNumber::Show: re = " << re << std::endl;
    }
};

class ComplexNumber: public RealNumber {
public:
    int im;

    ComplexNumber(int re_0, int im_0): RealNumber(re_0), im(im_0) {
        std::cout << "-- Constructor ComplexNumber" << std::endl;
    }
    void Show() {
        std::cout << "ComplexNumber::Show: re = " << re << " im = " << im << std::endl;
    }
};

int main()
{
    // int i;

    BaseNumber baseNumber;
    baseNumber.Show();

    std::cout << "\nCreate object of RealNumber" << std::endl;

    RealNumber realNumber(1);
    realNumber.Show();

    std::cout << "\nCreate object of ComplexNumber" << std::endl;

    ComplexNumber complexNumber(5, 50);
    complexNumber.Show();

    std::cout << "\nPolymorphism\n" << std::endl;

    // realNumber = complexNumber;
    // realNumber.Show();

    //--error-- complexNumber = realNumber;

    std::vector<BaseNumber*> v;

    v.push_back(&baseNumber);
    v.push_back(&realNumber);
    v.push_back(&complexNumber);

    std::cout << "v.size() = " << v.size() << std::endl;

    for (unsigned int i=0; i<v.size(); ++i) {
        BaseNumber *object = v[i];
        object->Show();
    }

    return 0;
}
