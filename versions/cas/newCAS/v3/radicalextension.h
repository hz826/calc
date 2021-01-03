#pragma once

#include "mainheader.h"
#include "factor.h"

class RadicalExtension {
public:
    Base base;
    Values value;

    void changebase(Base nbase);

public:
    friend RadicalExtension operator + (RadicalExtension A, RadicalExtension B);
    friend RadicalExtension operator - (RadicalExtension A, RadicalExtension B);
    friend RadicalExtension operator * (RadicalExtension A, RadicalExtension B);
    friend RadicalExtension operator / (RadicalExtension A, RadicalExtension B);

    void simp();

    RadicalExtension();
    RadicalExtension(Rational A);//A
    RadicalExtension(ll A, Rational B);//A^(p/q)
    RadicalExtension(Rational A, Rational B);//(ap/aq)^B = ap^B * aq ^(-B)

    double getDouble();

    void print();
};
