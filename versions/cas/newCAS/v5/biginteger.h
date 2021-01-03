#pragma once

#include "mainheader.h"
#include "algo.h"

class PInteger {
public:
    static constexpr int M = 9;
    static constexpr ll PM = 1e9;
    static int log10(ll x);
    static ll pow10(int x);
    static void output(std::ostream &out,ll x);
	ll *a;
    int n;

    PInteger();
    PInteger(int n);
    PInteger(const PInteger &A);
    PInteger(const std::string &s);
    ~PInteger();
    const PInteger& operator = (const PInteger &A);
    friend PInteger operator + (const PInteger &A,const PInteger &B);
    friend PInteger operator - (const PInteger &A,const PInteger &B);
    friend PInteger operator * (const PInteger &A,const PInteger &B);
    friend PInteger operator / (const PInteger &A,const PInteger &B);
    friend PInteger operator % (const PInteger &A,const PInteger &B);
    friend bool operator == (const PInteger &A,const PInteger &B);
    friend bool operator <  (const PInteger &A,const PInteger &B);
    friend std::ostream & operator << (std::ostream &out,const PInteger &A);

    int log10() const;
    PInteger shift(int d) const;
    static PInteger Int(ll x);
    double toDouble() const;
    ll toLongLong() const;
};

class Integer {
private:
    PInteger X;
    char symbol;//'+' or '-'
public:
    Integer();
    Integer(ll x);
    Integer(const PInteger &X,char symbol);
    Integer(const Integer &A);
    Integer(std::string s);
    friend Integer operator + (const Integer &A,const Integer &B);
    friend Integer operator - (const Integer &A,const Integer &B);
    friend Integer operator * (const Integer &A,const Integer &B);
    friend Integer operator / (const Integer &A,const Integer &B);
    friend Integer operator % (const Integer &A,const Integer &B);
    friend bool operator == (const Integer &A,const Integer &B);
    friend bool operator <  (const Integer &A,const Integer &B);
    friend std::istream & operator >> (std::istream &in,Integer &A);
    friend std::ostream & operator << (std::ostream &out,const Integer &A);
    double toDouble() const;
    ll toLongLong() const;
    bool canChangetoLongLong() const;
};