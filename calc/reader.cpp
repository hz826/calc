#include"reader.h"

Reader::Reader(std::string str){
    S = str;
    now = 0;
}

bool Reader::isDigit() {
    return '0' <= next() && next() <= '9';
}

bool Reader::isLetter() {
    return ('a' <= next() && next() <= 'z') || ('A' <= next() && next() <= 'Z');
}

void Reader::getnxt() {
    if (now < (int)S.length()) ++now;
}
char Reader::next() {
    return now < (int)S.length() ? S[now] : '`';
}

int Reader::readInt(){
    int res = 0;
    while (isDigit()) {
        res = res * 10 + (next()-'0');
        getnxt();
    }
    return res;
}

double Reader::readDouble(){
    double res = 0, scale = 1;
    while (isDigit()) {
        res = res * 10 + (next()-'0');
        getnxt();
    }
    if (next() == '.'){
        getnxt();
        while (isDigit()) {
            res = res * 10  + (next()-'0');
            scale *= 10;
            getnxt();
        }
    }
    return res /= scale;
}

Rational Reader::readRational() {
    Integer p = 0, q = 1;
    while (isDigit()) {
        p = p * 10 + (next()-'0');
        getnxt();
    }
    if (next() == '.'){
        getnxt();
        while (isDigit()) {
            p = p * 10  + (next()-'0');
            q = q * 10;
            getnxt();
        }
    }
    return Rational(p,q);
}

std::string Reader::readFunc(){
    std::string res = "";
    while (isLetter())
    {
        res += next();
        getnxt();
    }
    return res;
}
