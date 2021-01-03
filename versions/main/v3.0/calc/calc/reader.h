#ifndef READER_H
#define READER_H
#include<iostream>
#include<cmath>
#include<QString>
using namespace std;
class Reader {
    private:
        QString S;
        int now;

    public :
        Reader(QString str);
        bool isDigit();
        bool isLetter();
        void getnxt();
        char next();
        int readInt();
        double readDouble();
        QString readFunc();
};
#endif // READER_H
