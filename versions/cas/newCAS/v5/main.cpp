#include <iostream>
#include "mainheader.h"
#include "trig.h"
#include "radicalextension.h"
using namespace std;

namespace FinalTest {
    typedef Trig expr;

    template <typename T>
    expr sin(T d) { return Trig::sin(d); }
    template <typename T>
    expr cos(T d) { return Trig::cos(d); }
    template <typename T>
    expr tan(T d) { return Trig::tan(d); }

    typedef RadicalExtension RE;

    RE sqrt(ll a,ll p,ll q) {// a ^ {p/q}
        return RE(a,Rational(p,q));
    }
    RE sqrt2(ll a) {return sqrt(a,1,2);}
    RE sqrt3(ll a) {return sqrt(a,1,3);}

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
    }
#undef test
}

namespace RETest {
    typedef RadicalExtension RE;

    RE sqrt(ll a,ll p,ll q) {// a ^ {p/q}
        return RE(a,Rational(p,q));
    }
    RE sqrt2(ll a) {return sqrt(a,1,2);}
    RE sqrt3(ll a) {return sqrt(a,1,3);}

    void main() {
        RE A = sqrt(2,1,5);
        RE B = sqrt(2,1,3);
        A.print();  cout << endl;
        B.print();  cout << endl;
        RE C = A / B;
        C.print();  cout << endl;
    }
}

int main() {
    try {
//        FinalTest::main();
        RETest::main();
    } catch (const char* s) {
        cout << "CATCHED ERROR!  " << s << endl;
    }
}