#include "rational.h"

Rational::Rational() : p(0), q(1) { /*out << "new Rational" << std::endl;*/ }
Rational::Rational(const Integer& p) : p(p), q(1) {}
Rational::Rational(const Integer& p, const Integer& q) : p(p), q(q) { simp(); }
Rational::Rational(ll p) : p(Integer(p)), q(Integer(1)) {}
Rational::Rational(ll p, ll q) : p(Integer(p)), q(Integer(q)) { simp(); }

Rational::Rational(const Rational& R) : p(R.p), q(R.q) {}

Rational operator + (const Rational& A, const Rational& B) {
    return Rational(A.p * B.q + B.p * A.q, A.q*B.q);
}

Rational operator - (const Rational& A, const Rational& B) {
    return Rational(A.p * B.q - B.p * A.q, A.q * B.q);
}

Rational operator * (const Rational& A, const Rational& B) {
    return Rational(A.p * B.p, A.q * B.q);

}

Rational operator / (const Rational& A, const Rational& B) {
    return Rational(A.p * B.q, A.q * B.p);;
}

bool operator < (const Rational& A, const Rational& B) {//ap/aq < bp/bq
    return A.p * B.q < B.p* A.q;
}

bool operator == (const Rational& A, const Rational& B) {
    return A.p * B.q == B.p * A.q;
}

void Rational::simp() {
//    out << "test";
    if (q == Integer(0)) throw "Rational.simp : this rational is infinty";
    Integer g = Algo::gcd(p, q);
    p = p / g;  q = q / g;
    if (q < 0) { p = 0-p;  q = 0-q; }
}

Integer Rational::mod() {
    Integer m = p / q;
    p = p % q;
    if (p < 0) p = p + q, m = m-1;
    return m;
}

double Rational::getDouble() const { return 1.0 * p.toDouble() / q.toDouble(); }
void Rational::print(std::ostream &out) const {
    if (q == 1) out << p;
    else out << "{" << p << "/" << q << "}"; 
}

bool Rational::isInteger() const {
    return q == 1;
}

Integer Rational::toInteger() const {
    if (q == 1) return p;
    else throw "Rational::toInteger : Error, not a integer !";
}

Hash Rational::getHash() const {
    return p.getHash() * Hash(12842479,10481181) + q.getHash();
}

std::string Rational::toTeX() const {
    std::stringstream ss;
    std::string output;
    if (q == 1) ss << p;
    else ss << "\\frac{" << p << "}{" << q << "}";
    ss >> output;
    return output;
}