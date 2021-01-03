#include"number.h"
using namespace std;

double Number::qpow(double a,long long x){
    double r = 1;
    bool flag = false;
    if (x < 0){
        x = -x;
        flag = true;
    }
    for (;x;x>>=1){
        if (x & 1) r *= a;
        a *= a;
    }
    if (flag) r = 1.0 / r;
        return r;
}

bool Number::isInteger(){
    return fabs(round(v) - v) < 1e-7;
}
Number Number::PI() {return Number(acos(-1));}
Number Number::E() {return Number(exp(1));}
Number Number::abs(Number a) {return Number(std::abs(a.v));}
Number Number::sin(Number a) {return Number(std::sin(a.v));}
Number Number::cos(Number a) {return Number(std::cos(a.v));}
Number Number::tan(Number a) {return Number(std::tan(a.v));}
Number Number::ln(Number a) {
    if (a.v < 0) throw "ln : a<0";
    return Number(std::log(a.v));
}
Number Number::lg(Number a)  {
    if (a.v < 0) throw "lg : a<0";
    return Number(std::log10(a.v));
}
Number Number::log(Number a,Number b) {
    if (a.v < 0) throw "log : a<0";
    if (a.v == 1) throw "log : a=1";
    if (b.v < 0) throw "log : b<0";
    return Number(std::log(b.v) / std::log(a.v));
}
    Number Number::sqrt(Number a) {
    if (a.v < 0) throw "sqrt : a<0";
    return Number(std::sqrt(a.v));
}
    Number Number::sqrtn(Number a,Number b) {
    return a ^ (Number(1) / b);
}
