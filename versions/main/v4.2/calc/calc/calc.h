#ifndef CALC_H
#define CALC_H

/* calc.h
 *
 * 数学表达式计算
 * 使用template, 可以处理多种类型
 */
#include "reader.h"

template<typename T>
class M {
public:
    T t;
    bool empty;
    M() : t(0), empty(true) {}
    M(const T& t) : t(t), empty(false) {}
};

template<typename T>
class Calc {
    private:
        Reader R;
        T readFunc();
        M<T> read4();
        M<T> read3();
        M<T> read2();
        M<T> read1();
        T readBracket(char lc,char rc);
    public:
        Calc(std::string str);
        T get();
};

template<typename T>
Calc<T>::Calc(std::string str) : R(str) {

}

template<typename T>
T Calc<T>::readFunc() {
    std::string func = R.readFunc();
    if (func == "E") return T::E();
    else if (func == "PI") return T::PI();
    else if (func == "abs") return T::abs(readBracket('{','}'));
    else if (func == "sin") return T::sin(readBracket('(',')'));
    else if (func == "cos") return T::cos(readBracket('(',')'));
    else if (func == "tan") return T::tan(readBracket('(',')'));
    else if (func == "ln") return T::ln(readBracket('(',')'));
    else if (func == "lg") return T::lg(readBracket('(',')'));
    else if (func == "log") {
        T A = readBracket('{','}');
        T B = readBracket('{','}');
        return T::log(A,B);
    }
    else if (func == "sqrtn") {
        T A = readBracket('{','}');
        T B = readBracket('{','}');
        return T::sqrtn(B,A);
    }
    else if (func == "frac") {
        T A = readBracket('{','}');
        T B = readBracket('{','}');
        return A / B;
    }
    else if (func == "sqrt") return T::sqrt(readBracket('{','}'));
    else throw "unknown function";
}

template<typename T>
M<T> Calc<T>::read4() {
    M<T> Left;
    if (R.isDigit()) {
        Left = M<T>(T(R));
    } else if (R.next() == '(') {
        T Right = readBracket('(',')');
        if (Left.empty) Left = M<T>(T(1));
        Left.t = Left.t * Right;
    } else if (R.next() == '\\') {
        R.getnxt();
        T Right = readFunc();
        if (Left.empty) Left = M<T>(T(1));
        Left.t = Left.t * Right;
    }
    return Left;
}

template<typename T>
M<T> Calc<T>::read3() {
    M<T> Left = read4();
    while (R.next() == '^') {
        R.getnxt();
        M<T> Right = readBracket('{','}');
        if (Left.empty || Right.empty) throw "empty argument !";
        Left.t = Left.t ^ Right.t;
    }
    return Left;
}

template<typename T>
M<T> Calc<T>::read2() {
    M<T> Left = read3();
    while (R.next() == '*' || R.next() == '/' || R.next() == '\\' || R.next() == '(') {
        char tmp = R.next();
        if (R.next() == '*' || R.next() == '/') R.getnxt();
        M<T> Right = read3();
        if (Left.empty || Right.empty) throw "empty argument !";
        if (tmp == '/') Left.t = Left.t / Right.t;
        else Left.t = Left.t * Right.t;
    }
    return Left;
}

template<typename T>
M<T> Calc<T>::read1() {
    M<T> Left = read2();
    while (R.next() == '+' || R.next() == '-') {
        char tmp = R.next();
        R.getnxt();
        M<T> Right = read2();
        if (Right.empty) throw "empty argument !";
        if (tmp == '+') Left.t = Left.t + Right.t;
        if (tmp == '-') Left.t = Left.t - Right.t;
        Left.empty = false;
    }
    return Left;
}

template<typename T>
T Calc<T>::readBracket(char lc,char rc) {
    char Left = R.next();
    if (Left != lc) throw "unknown symbol";
    R.getnxt();
    M<T> res = read1();
    char Right = R.next();
    if (Right != rc) throw "unmatched brace";
    R.getnxt();
    if (res.empty) throw "empty bracet";
    return res.t;
}

template<typename T>
T Calc<T>::get() {
    M<T> res = read1();
    if (R.next() != '`') throw "syntax error";
    return res.t;
}

#endif
