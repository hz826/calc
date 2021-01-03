#ifndef READER_H
#define READER_H
#include<iostream>
#include<cmath>
#include<QString>
using namespace std;
class Reader {
    private:
        string S;
        int now;

    public :
        Reader(string str);
        bool isDigit();
        bool isLetter();
        void getnxt();
        char next();
        int readInt();
        double readDouble();
        string readFunc();
};
#endif // READER_H
