#include "rational.h"

Rational::Rational() : p(0), q(1) {}
Rational::Rational(ll p) : p(p), q(1) {}
Rational::Rational(ll p, ll q) : p(p), q(q) { simp(); }
Rational::Rational(const Rational& R) : p(R.p), q(R.q) {}

Rational operator + (Rational A, Rational B) {
    Rational C(A.p * B.q + B.p * A.q, A.q*B.q);
    C.simp();
    return C;
}

Rational operator - (Rational A, Rational B) {
    Rational C(A.p * B.q - B.p * A.q, A.q * B.q);
    C.simp();
    return C;
}

Rational operator * (Rational A, Rational B) {
    Rational R(A.p * B.p, A.q * B.q);
    R.simp();
    return R;
}

Rational operator / (Rational A, Rational B) {
    Rational R(A.p * B.q, A.q * B.p);
    R.simp();
    return R;
}

bool operator < (Rational A, Rational B) {//ap/aq < bp/bq
    return A.p * B.q < B.p* A.q;
}

bool operator == (Rational A, Rational B) {
    return A.p * B.q == B.p * A.q;
}

void Rational::simp() {
    if (q == 0) throw "Rational.simp : divided by zero";
    ll g = Algo::gcd(p, q);
    p /= g;  q /= g;
    if (q < 0) { p = -p;  q = -q; }
}

ll Rational::mod() {
    ll m = p / q;  p %= q;
    if (p < 0) p += q, --m;
    return m;
}

double Rational::getDouble() const { return 1.0 * p / q; }
void Rational::print() const {
    if (q == 1) std::cout << p;
    else std::cout << "{" << p << "/" << q << "}"; 
}