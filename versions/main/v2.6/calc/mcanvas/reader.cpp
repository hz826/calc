#include"reader.h"
Reader::Reader(string str){
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

string Reader::readFunc(){
    string res = "";
    while (isLetter())
    {
        res += next();
        getnxt();
    }
    return res;
}
