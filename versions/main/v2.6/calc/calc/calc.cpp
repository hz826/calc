#include"calc.h"
#include"mcanvas\number.h"
template<typename T>
Calc<T>::Calc(string str) : R(str) {

}

template<typename T>
T Calc<T>::readFunc() {
    string func = R.readFunc();
    T res;
    if (func == "E") return Number::E();
    if (func == "PI") return Number::PI();
    if (func == "abs") return Number::abs(readBracket('{','}'));
    if (func == "sin") return Number::sin(readBracket('(',')'));
    if (func == "cos") return Number::cos(readBracket('(',')'));
    if (func == "tan") return Number::tan(readBracket('(',')'));
    if (func == "ln") return Number::ln(readBracket('(',')'));
    if (func == "lg") return Number::lg(readBracket('(',')'));
    if (func == "log") return Number::log(readBracket('{','}'),readBracket('{','}'));
    if (func == "sqrtn") return Number::log(readBracket('{','}'),readBracket('{','}'));
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



