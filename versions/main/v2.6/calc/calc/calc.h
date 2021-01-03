#ifndef CALC_H
#define CALC_H
#include<iostream>
#include<cmath>
#include<QString>
#include"mcanvas\reader.h"
using namespace std;
/* calc.h
 *
 * 数学表达式计算
 * 使用template, 可以处理多种类型
 */


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
        Calc(string str);
        T get();
};

#endif // CALC_H
