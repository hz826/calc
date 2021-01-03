#pragma once

#include "mainheader.h"
#include "algo.h"

class Rational {//��������
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

    void simp();//����ͨ��
    ll mod();//��Ϊ�������������������
    double getDouble() const;
    void print() const;
};