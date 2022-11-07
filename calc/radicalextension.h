#pragma once

#include "factor.h"

class RadicalExtension {
public:
    Base base;
    Values value;

    void changebase(Base nbase);

public:
    friend bool operator == (RadicalExtension A, RadicalExtension B);
    friend RadicalExtension operator + (RadicalExtension A, RadicalExtension B);
    friend RadicalExtension operator - (RadicalExtension A, RadicalExtension B);
    friend RadicalExtension operator * (RadicalExtension A, RadicalExtension B);
    friend RadicalExtension operator / (RadicalExtension A, RadicalExtension B);

    void simp();

    RadicalExtension();
    RadicalExtension(ll x);
    RadicalExtension(Rational A);//A
    RadicalExtension(ll A, Rational B);//A^(p/q)
    RadicalExtension(Rational A, Rational B);//(ap/aq)^B = ap^B * aq ^(-B)

    double getDouble() const;
    void print(std::ostream &out) const;

    bool isRational() const;
    Rational toRational() const;
    bool isInteger() const;
    Integer toInteger() const;

    Hash getHash() const;

    std::string toTeX() const;
};
