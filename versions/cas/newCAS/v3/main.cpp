#include "mainheader.h"
#include "trig.h"
#include "radicalextension.h"

namespace TrigTest {
    using namespace std;
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

namespace LETest {
    using namespace std;

    int f1(int x,int p,int s) {
        int a = s, b = a^(a*a), c = b^(b*b), d = c^(c*c);
        return ((((1ll*x+a)*x+b)*x+c)*x+d) % p;
    }
    int f(int x) {
        return f1(x,93,3) ^ f1(x,101,5);
    }
    Rational f(int i,int j) {
        return Rational(f(i*100+j),f((i*100+j)*100));
    }

    void main() {
//        int n = 5;
//        vector<vector<Rational> > A;
//        A.resize(n);
//        for (int i=0;i<n;i++) A[i].resize(n+1);
//        for (int i=0;i<n;i++) for (int j=0;j<=n;j++) A[i][j] = f(i,j);
//        vector<Rational> ans = Algo::solve(A);
//        for (int i=0;i<n;i++) {
//            ans[i].print();
//            cout << endl;
//        }
    }
}

namespace RETest {
    using namespace std;
    typedef RadicalExtension RE;

    RE sqrt(ll a,ll p,ll q) {// a ^ {p/q}
        return RE(a,Rational(p,q));
    }
    RE sqrt2(ll a) {return sqrt(a,1,2);}
    RE sqrt3(ll a) {return sqrt(a,1,3);}

#define test(x) \
    {           \
        RE y = x; \
        y.base.print(y.base);  cout << endl;        \
        cout << #x << endl;      \
        cout << "=  ";  \
        y.print();\
        cout << endl << endl;\
    }

    void main() {
//        RE now = RE(-1);
//        for (int i=0;i<10;i++) now = now * RE(25);
//        now.print();
//        cout << endl;

        RE A = sqrt2(14) * sqrt3(15);
        test(A / sqrt2(5));

        //test(RE(1) / (RE(1) + sqrt2(2)));
        //test((RE(2) - sqrt2(3)) / (RE(2) + sqrt2(3)));
        //test((sqrt(2,1,2) + sqrt(2,1,3)) * (sqrt(2,1,2) + sqrt(2,1,3)));
    }

#undef test
}

int main() {
    try {
//        TrigTest::main();
//        LETest::main();
        RETest::main();
    }
    catch (const char* s) {
        std::cout << "error : " << s << std::endl;
    }
}