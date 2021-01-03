#pragma once

#include "mainheader.h"
#include "algo.h"
#include "rational.h"

/*
    RadicalExtension（根式扩张域) ：
        举例：Q(2^(1/2)) = a + b*2^(1/2)
              Q(2^(1/3),5^(1/2)) = a + b*2^(1/3) + c*2^(2/3) + d*5^(1/2) + e*2^(1/3)*5^(1/2) + f*2^(2/3)*5^(1/2)

    Base（根式扩张域 的基）：
        假设当前 根式扩张域 为 Q(p1^(1/a1), p2^(1/a2), ...) ,其中 p1,p2,... 为质数
        则基为 map{ (p1,a1), (p2,a2), ... }, 其中ai为>1的整数

    Factor（因子）
        当前 根式扩张域 的 因子 可表示为 F = p1^(b1/a1) * p2^(b2/a2), ... ，其中 p1,p2,... 为质数，bi为 [0,ai) 的整数
        所以 根式扩张域 中的每一个元素 都可表示为 
            alpha1 * F1 + alpha2 * F2 + ... ，其中 alpha1,alpha1,...是有理数 ，因子 F1,F2,... 两两不等

    为方便储存，Base 能将通过 encode 将该 Base 下的 Factor 转化为一个非负整数，通过 decode 还原
*/
class Factor : public std::map<ll, ll> {
};

class Base : public Factor {
private:
public:
    friend Base operator | (Base X, Base Y);

    ll encode(const Factor &F);
    Factor decode(ll x);
    double getDouble(const Factor &F);
    void print(const Factor &F);
};

class Values : public std::map<ll, Rational> {
};