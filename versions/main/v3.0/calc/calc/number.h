#ifndef NUMBER_H
#define NUMBER_H
#include<iostream>
#include<QString>
#include<cmath>

#include "reader.h"

class Number {
private:
    static double qpow(double a,long long x);
    bool isInteger();
public:
    Number() : v(0) {}
    Number(int v) : v(v) {}
    Number(double v) : v(v) {}
    Number(Reader &R) {v = R.readDouble();}

    double v;
    friend Number operator + (Number A,Number B) {return Number(A.v+B.v);}
    friend Number operator - (Number A,Number B) {return Number(A.v-B.v);}
    friend Number operator * (Number A,Number B) {return Number(A.v*B.v);}
    friend Number operator / (Number A,Number B){
      if (B.v == 0.0) throw "divied by zero!";
      return Number(A.v/B.v);
    }
    friend Number operator ^ (Number A, Number B){
      if (B.isInteger()) return Number(std::pow(A.v,round(B.v)));
      else if (B.v < 0) throw "base is negative!";
      return Number(std::pow(A.v,B.v));//in cmath
    }
    static Number PI();
    static Number E();
    static Number abs(Number a);
    static Number sin(Number a);
    static Number cos(Number a);
    static Number tan(Number a);
    static Number ln(Number a);
    static Number lg(Number a);
    static Number log(Number a,Number b);
    static Number sqrt(Number a);
    static Number sqrtn(Number a,Number b);
};

#endif // NUMBER_H

