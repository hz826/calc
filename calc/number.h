#ifndef NUMBER_H
#define NUMBER_H

#include "mainheader.h"
#include "reader.h"

class Number {
private:
    static double qpow(double a,long long x) {
        double r = 1;
        bool flag = false;
        if (x < 0) {
            x = -x;
            flag = true;
        }
        for (;x;x>>=1) {
            if (x & 1) r *= a;
            a *= a;
        }
        if (flag) r = 1.0 / r;
        return r;
    }

    bool isInteger() {
        return fabs(round(v) - v) < 1e-7;
    }

public:
    Number() : v(0) {}
    Number(int v) : v(v) {}
    Number(double v) : v(v) {}
    Number(Reader &R) {v = R.readDouble();}

    double v;
    friend Number operator + (Number A,Number B) {return Number(A.v+B.v);}
    friend Number operator - (Number A,Number B) {return Number(A.v-B.v);}
    friend Number operator * (Number A,Number B) {return Number(A.v*B.v);}
    friend Number operator / (Number A,Number B) {
        if (B.v == 0.0) throw "divied by zero!";
        return Number(A.v/B.v);
    }
    friend Number operator ^ (Number A,Number B) {
        if (B.isInteger()) return Number(std::pow(A.v,round(B.v)));
        else if (A.v < 0) throw "base is negative!";
        return Number(std::pow(A.v,B.v));//in cmath
    }

    static Number PI() {return Number(acos(-1));}
    static Number E() {return Number(exp(1));}
    static Number abs(Number a) {return Number(std::abs(a.v));}
    static Number sin(Number a) {return Number(std::sin(a.v));}
    static Number cos(Number a) {return Number(std::cos(a.v));}
    static Number tan(Number a) {return Number(std::tan(a.v));}
    static Number ln(Number a)  {
        if (a.v < 0) throw "ln : a<0";
        return Number(std::log(a.v));
    }
    static Number lg(Number a)  {
        if (a.v < 0) throw "lg : a<0";
        return Number(std::log10(a.v));
    }
    static Number log(Number a,Number b) {
        if (a.v < 0) throw "log : a<0";
        if (a.v == 1) throw "log : a=1";
        if (b.v < 0) throw "log : b<0";
        return Number(std::log(b.v) / std::log(a.v));
    }
    static Number sqrt(Number a) {
        if (a.v < 0) throw "sqrt : a<0";
        return Number(std::sqrt(a.v));
    }
    static Number sqrtn(Number a,Number b) {
        return a ^ (Number(1) / b);
    }
};

#endif // NUMBER_H

