#pragma once

#include "poly.h"

class Trig {
public:
	SPoly p, q, cyc;//p = \sum e^{\aplha \pi i}, where -\frac12 < \alpha < \frac12
    ll base;

    Trig();
    Trig(SPoly p,SPoly q,ll base);
    Trig(Rational R);
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
};