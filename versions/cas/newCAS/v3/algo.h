#pragma once

#include "mainheader.h"

class Algo {//算法类，所有成员均为static
private:
    template<typename T>
    static T det(std::vector<std::vector<T>> &A,int n) {
        T sum(0), r(1);
        std::cout << "Det : " << std::endl;
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) {
                A[i][j].print();
                std::cout << " | ";
            }
            std::cout << std::endl;
        }

        std::vector<int> p;
        p.resize(n);
        for (int i=0;i<n;i++) p[i] = i;
        do {
            T now = r;
            for (int i=0;i<n;i++) now = now * A[i][p[i]];
            sum = sum + now;
            r = T(0) - r;
        } while (std::next_permutation(p.begin(),p.end()));

        std::cout << "= ";
        sum.print();
        std::cout << std::endl << std::endl;
        return sum;
    }

public:
    template<typename T>
    static T abs(T x) {//绝对值
        return x < 0 ? 0-x : x;
    }

    template<typename T>
    static T gcd(T x, T y) {//最大公约数
        return (y == 0) ? x : gcd(y, x % y);
    }

    template<typename T>
    static T lcm(T x, T y) {//最小公倍数
        return x / gcd(x, y) * y;
    }

    static ll mu(ll x) {//莫比乌斯函数
        if (x == 1) return 1;
        auto M = factorize(x);
        for (auto& x : M) if (x.second > 1) return 0;
        if (M.size() % 2 == 0) return 1;
        else return -1;
    }

    static std::map<ll, ll> factorize(ll x) {
        std::map<ll, ll> res;

        for (ll i = 2; i * i <= x; ++i) if (x % i == 0) {
                ll tmp = 0;
                while (x % i == 0) {
                    x /= i;
                    ++tmp;
                }
                res[i] = tmp;
            }
        if (x > 1) res[x] = 1;
        return res;
    }
    /*
        分解质因数，以后可能会采用更高效的pollard's rho 算法，返回map<质数，次方>
        factorize(24) = map { (2,3) , (3,1) };
    */


    //由于一些未知的原因，template函数只能在头文件中实现
    template<typename T>
    static T qpow(T a, ll x) {//a^x
        bool flag = false;
        if (x < 0) x = -x, flag = true;
        T r = T(1);
        for (; x; x >>= 1) {
            if (x & 1) r = r * a;
            a = a * a;
        }
        if (flag) r = T(1) / r;
        return r;
    }
    /*
        计算某个域中元素的整数次方
        qpow(Rational(-2,3), -3) = Rational(-27,8);
    */
    template<typename T>
    static std::vector<T> solve(std::vector<std::vector<T> > A, std::vector<T> B) { //用克拉默法则解方程
        int n = A.size();
        for (int i=0;i<n;i++) if ((int)A[i].size() != n) throw "not a matrix";
        T D = det(A,n);
        std::vector<T> result;
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) std::swap(A[j][i],B[j]);
            T tmp = det(A,n);
            result.push_back(tmp / D);
            for (int j=0;j<n;j++) std::swap(A[j][i],B[j]);
        }
        return result;
    }
};