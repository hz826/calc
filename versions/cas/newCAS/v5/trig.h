#pragma once

#include "poly.h"

class Trig {
public:
    static const RadicalExtension c15, c30, c45;//base = 12, 6, 4, 3

	SPoly p, q, cyc;//p = \sum e^{\aplha \pi i}, where -\frac12 < \alpha < \frac12
    ll base;

    Trig();
    Trig(ll x);
    Trig(Rational R);
    Trig(RadicalExtension R);
    Trig(SPoly p,SPoly q,ll base);
    static Trig sin(Rational alpha);
    static Trig cos(Rational alpha);
    static Trig tan(Rational alpha);
    static Trig sin(ll deg);
    static Trig cos(ll deg);
    static Trig tan(ll deg);

    friend Trig operator + (Trig A, Trig B);
    friend Trig operator - (Trig A, Trig B);
    friend Trig operator * (Trig A, Trig B);
    friend Trig operator / (Trig A, Trig B);

    void simp();//上下通分
    void changeBase(ll nbase);
    std::complex<double> getDouble();
    void printexp();
    void printtrig();
    void printtrig(SPoly &p);

    void getCyclotomicPolynomial();
};