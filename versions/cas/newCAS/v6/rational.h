#pragma once

#include "biginteger.h"

class Rational {//有理数类
private:
public:
    Integer p, q;
    Rational();
    Rational(const Integer& p);
    Rational(const Integer& p, const Integer& q);
    Rational(ll p);
    Rational(ll p, ll q);
    Rational(const Rational& R);

    friend Rational operator + (const Rational &A, const Rational &B);
    friend Rational operator - (const Rational &A, const Rational &B);
    friend Rational operator * (const Rational &A, const Rational &B);
    friend Rational operator / (const Rational &A, const Rational &B);
    friend bool operator <  (const Rational &A, const Rational &B);
    friend bool operator == (const Rational &A, const Rational &B);

    void simp();//上下通分
    Integer mod();//化为真分数，返回整数部分
    double getDouble() const;
    void print() const;

    bool isInteger() const;
    Integer toInteger() const;

    Hash getHash() const;

    string toTeX() const;
};