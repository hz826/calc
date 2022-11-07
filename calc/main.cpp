#include <iostream>
#include "mainheader.h"
#include "calc.h"
#include "expr.h"
#include "number.h"
using namespace std;

namespace FinalTest {
    using namespace std;
    void main() {
        Number nans;
        nans = Calc<Number>("\\E*(\\E^{\\E})").get();
        cout << nans.v << endl;
        nans = Calc<Number>("\\E(\\E)^{\\E}").get();
        cout << nans.v << endl;

        Expr eans;
        eans = Calc<Expr>("\\cos(\\frac{1}{6}\\PI)").get();
        cout << eans.toTeX() << endl;
    }
#undef test
}

int main() {
    try {
        FinalTest::main();
    } catch (const char* s) {
        cout << "CATCHED ERROR!  " << s << endl;
    }
}
