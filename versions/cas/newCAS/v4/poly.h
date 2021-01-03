#pragma once

#include "mainheader.h"
#include "algo.h"
#include "rational.h"

class Poly : public std::map<ll, Rational> {
public:
    Poly();
    Poly(Rational R);

    friend Poly operator + (Poly A, Poly B);
    friend Poly operator - (Poly A, Poly B);
    friend Poly operator * (Poly A, Poly B);
    friend Poly operator / (Poly A, Poly B);

    ll deg();
    void simp();
    void print(const std::string& var);

    static Poly xn(ll n);
    static Poly cyclotomic_polynomial(ll n);
    /*
        用莫比乌斯反演计算分圆多项式
        \Phi(n) = \prod_{d\mid n} (x^d-1)^{\mu(\frac nd)}
     */
};

class SPoly : public std::map<ll, Rational> {
public:
    SPoly();
    SPoly(Rational R);

    friend SPoly operator + (SPoly A, SPoly B);
    friend SPoly operator - (SPoly A, SPoly B);
    friend SPoly operator * (SPoly A, SPoly B);
    friend SPoly operator / (SPoly A, SPoly B);
    friend SPoly operator % (SPoly A, SPoly B);

    ll deg();
    void simp();
    void print(const std::string& var);
    bool check();
    std::complex<double> getDouble(std::complex<double> x);

    static SPoly gcd(SPoly p, SPoly q);
    static SPoly xn(ll n);
    static SPoly cyclotomic_polynomial(ll n);
};