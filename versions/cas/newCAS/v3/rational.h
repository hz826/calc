#pragma once

#include "mainheader.h"
#include "algo.h"

class Rational {//有理数类
private:
public:
    ll p, q;
    Rational();
    Rational(ll p);
    Rational(ll p, ll q);
    Rational(const Rational& R);

    friend Rational operator + (Rational A, Rational B);
    friend Rational operator - (Rational A, Rational B);
    friend Rational operator * (Rational A, Rational B);
    friend Rational operator / (Rational A, Rational B);
    friend bool operator <  (Rational A, Rational B);
    friend bool operator == (Rational A, Rational B);

    void simp();//上下通分
    ll mod();//化为真分数，返回整数部分
    double getDouble() const;
    void print() const;
};