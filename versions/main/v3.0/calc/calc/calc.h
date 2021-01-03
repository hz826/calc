#ifndef CALC_H
#define CALC_H

#include <cmath>
#include <QString>

/* calc.h
 *
 * 数学表达式计算
 * 使用template, 可以处理多种类型
 */
#include "reader.h"
#include "number.h"
#include <cmath>
using namespace std;

template<typename T>
class Calc {
    private:
        Reader R;
        T readFunc();
        T read4();
        T read3();
        T read2();
        T read1();
        T readBracket(char lc,char rc);
    public:
        Calc(QString str);
        T get();
};

template<typename T>
Calc<T>::Calc(QString str) : R(str) {

}

template<typename T>
T Calc<T>::readFunc() {
    QString func = R.readFunc();
    T res;
    if (func == "E") return Number::E();
    if (func == "PI") return Number::PI();
    if (func == "deg") return Number::PI() / Number(180);
    if (func == "abs") return Number::abs(readBracket('{','}'));
    if (func == "sin") return Number::sin(readBracket('(',')'));
    if (func == "cos") return Number::cos(readBracket('(',')'));
    if (func == "tan") return Number::tan(readBracket('(',')'));
    if (func == "ln") return Number::ln(readBracket('(',')'));
    if (func == "lg") return Number::lg(readBracket('(',')'));
    if (func == "log") {
        T A = readBracket('{','}');
        T B = readBracket('{','}');
        return Number::log(A,B);
    }
    if (func == "sqrtn") {
        T A = readBracket('{','}');
        T B = readBracket('{','}');
        return Number::sqrtn(B,A);
    }
    if (func == "frac") {
        T A = readBracket('{','}');
        T B = readBracket('{','}');
        return A / B;
    }
    if (func == "sqrt") return Number::sqrt(readBracket('{','}'));
    return res;
}

template<typename T>
T Calc<T>::read4() {
    T Left(1);
    if (R.next() == '-') {
        R.getnxt();
        Left = T(-1);
    }

    for (bool flag = true;flag;) {
        T Right;

        switch (R.next()) {
            case '(' :
                Right = readBracket('(',')');
                break;

            case '\\' :
                R.getnxt();
                Right = readFunc();
                break;

            default :
                if (!R.isDigit()) {
                    flag = false;
                    break;
                }
                Right = T(R);
        }
        if (flag) Left = Left * Right;
    }
    return Left;
}

template<typename T>
T Calc<T>::read3() {
    T Left = read4();
    while (R.next() == '^') {
        R.getnxt();
        T Right = readBracket('{','}');
        Left = Left ^ Right;
    }
    return Left;
}

template<typename T>
T Calc<T>::read2() {
    T Left = read3();
    while (R.next() == '*' || R.next() == '/') {
        char tmp = R.next();
        R.getnxt();
        T Right = read3();
        if (tmp == '*') Left = Left * Right;
        if (tmp == '/') Left = Left / Right;
    }
    return Left;
}

template<typename T>
T Calc<T>::read1() {
    T Left = read2();
    while (R.next() == '+' || R.next() == '-') {
        char tmp = R.next();
        R.getnxt();
        T Right = read2();
        if (tmp == '+') Left = Left + Right;
        if (tmp == '-') Left = Left - Right;
    }
    return Left;
}

template<typename T>
T Calc<T>::readBracket(char lc,char rc) {
    char Left = R.next();
    if (Left != lc) throw "unknown symbol";
    R.getnxt();
    T res = read1();
    char Right = R.next();
    if (Right != rc) throw "unmatched brace";
    R.getnxt();
    return res;
}

template<typename T>
T Calc<T>::get() {
    T res = read1();
    if (R.next() != '`') throw "syntax error";
    return res;
}

#endif
