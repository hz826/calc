#pragma once

#include "biginteger.h"

class Rational {//��������
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

    void simp();//����ͨ��
    Integer mod();//��Ϊ�������������������
    double getDouble() const;
    void print() const;

    bool isInteger() const;
    Integer toInteger() const;

    Hash getHash() const;

    string toTeX() const;
};