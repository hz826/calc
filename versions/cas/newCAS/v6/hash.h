#pragma once

#include "mainheader.h"
#include "algo.h"

class Hash {
public:
    static constexpr ll P1 = 1e9+7, P2 = 1e9+9;

    ll h1, h2;
    Hash() : h1(0), h2(0) {}
    Hash(ll h) : h1((h%P1+P1)%P1), h2((h%P2+P2)%P2) {}
    Hash(ll h1, ll h2) : h1((h1%P1+P1)%P1), h2((h2%P2+P2)%P2) {}

    const Hash& operator = (const Hash &A) {h1 = A.h1;  h2 = A.h2;  return *this;}
    friend Hash operator + (const Hash &A,const Hash &B) {return Hash(A.h1+B.h1, A.h2+B.h2);}
    friend Hash operator - (const Hash &A,const Hash &B) {return Hash(A.h1-B.h1, A.h2-B.h2);}
    friend Hash operator * (const Hash &A,const Hash &B) {return Hash(A.h1*B.h1, A.h2*B.h2);}
    friend bool operator < (const Hash &A,const Hash &B) {
        return (A.h1 < B.h1) || (A.h1 == B.h1 && A.h2 < B.h2);
    }
    friend bool operator == (const Hash &A,const Hash &B) {return A.h1 == B.h1 && A.h2 == B.h2;}

    void print() const {
        cout << "Hash(" << h1 << "," << h2 << ")";
    }
};