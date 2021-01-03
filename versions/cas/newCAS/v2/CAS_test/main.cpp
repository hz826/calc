#include <iostream>
#include "mainheader.h"
#include "trig.h"
using namespace std;

namespace TrigTest {
    typedef Trig expr;

    template <typename T>
    expr sin(T d) { return Trig::sin(d); }
    template <typename T>
    expr cos(T d) { return Trig::cos(d); }
    template <typename T>
    expr tan(T d) { return Trig::tan(d); }

#define test(x) \
    {\
        expr y = x; \
        cout << "simplifying : " << #x << endl; \
        cout << "exp__mode    : ";  y.printexp(); \
        cout << "trig_mode    : ";  y.printtrig(); \
        cout << "double : " << y.getDouble() << std::endl; \
        cout << endl << endl; \
    }

    void main() {
        test(cos(20))
        test(cos(20) + cos(40) + cos(80));//cos(20°) + cos(40°) + cos(80°)
        test(cos(10) * cos(10) + cos(50) * cos(50) - sin(40) * sin(80));
        test(cos(10) * cos(10) + sin(10) * sin(10));
        test((Rational(2) * cos(5) - sin(25)) / cos(25));
        test(sin(10) * sin(10) + cos(40) * cos(40) + sin(10) * cos(40));
        test(sin(20) * sin(40) * sin(80));
        test(sin(50) * (Rational(1) + Rational(2) * cos(30) * tan(10)));
        test(cos(70) + cos(1));
        test(cos(Rational(2, 7)) + cos(Rational(4, 7)) + cos(Rational(6, 7)));//cos(2pi/7)+cos(4pi/7)+cos(6pi/7)
        test(tan(Rational(1,8)));
        test(cos(50) + cos(20) + cos(10));
    }
#undef test
}

void f(SPoly A,SPoly B) {

}

int main() {
    try {
        TrigTest::main();
    } catch (const char* s) {
        cout << "CATCHED ERROR!  " << s << endl;
    }
}