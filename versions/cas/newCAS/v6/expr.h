#pragma once

#include "mainheader.h"
#include "trig.h"

class Expr {
    typedef Trig Number;
public:
    static map<Hash, Expr*> Expr_hashmap;
    static void HashInsert(Expr *p);
    static void HashClear();

    enum {
        OTHER,
        pi,
        e,
        NUM,
        SUM,
        MUL,
        POW,
        ABS,
        SIN,
        COS,
        TAN,
        LN,
    } TYPE;

    Number Num;
    map<Hash, Number > Sum;//Num * SUM //Num == 1
    map<Hash, Rational> Mul;//Num * Mul
    Expr* F, *F2;//NUM * f(F)

    Hash hash;

    Expr();
    Expr(ll R);
    Expr(Rational R);
    Expr(Number R);
    //Expr(Reader &R) {v = R.readDouble();}

    void simp();
    Hash calcHash();
    Hash getHash() const;

    static Expr add(Expr &A,Expr &B,char mode);
    static Expr mul(Expr &A,Expr &B,char mode);

    friend Expr operator + (Expr A,Expr B);
    friend Expr operator - (Expr A,Expr B);
    friend Expr operator * (Expr A,Expr B);
    friend Expr operator / (Expr A,Expr B);
    friend Expr operator ^ (Expr A,Expr B);

    static Expr PI();
    static Expr E();
    static Expr abs(Expr a);
    static Expr sin(Expr a);
    static Expr cos(Expr a);
    static Expr tan(Expr a);
    static Expr ln(Expr a);
    static Expr lg(Expr a);
    static Expr log(Expr a,Expr b);
    static Expr sqrt(Expr a);
    static Expr sqrtn(Expr a,Expr b);

    void print() const;
    string toTeX() const;
};