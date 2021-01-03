#include "mainheader.h"
#include "Expr.h"
using namespace std;

namespace FinalTest {
    void main() {
        Expr A = Expr::PI();
        cout << A.toTeX() << endl;
        Expr B = Expr(Rational(1,3));
        cout << B.toTeX() << endl;
        Expr C = A*B;
        cout << C.toTeX() << endl;
        Expr D = Expr::sin(C);
        cout << D.toTeX() << endl;
        Expr E = Expr::lg(D);
        cout << E.toTeX() << endl;

//        Trig A = Trig::sin(60) * Trig::tan(20);
//        cout << A.toTeX() << endl;

//        Expr A = Rational(1,3) * Expr::PI();
//        Expr B = Expr::PI();
//        cout << "A: ";  A.print();
//        cout << "B: ";  B.print();
//        Expr C = A ^ B;
//        cout << "C: ";  C.print();
//        cout << "--------------------- where : ---------------------" << endl;
//        for (auto &p : Expr::Expr_hashmap) p.second->print();
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
