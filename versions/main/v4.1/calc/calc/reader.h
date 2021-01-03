#ifndef READER_H
#define READER_H

#include "mainheader.h"
#include "rational.h"

class Reader {
    private:
        std::string S;
        int now;

    public :
        Reader(std::string str);
        bool isDigit();
        bool isLetter();
        void getnxt();
        char next();
        int readInt();
        double readDouble();
        Rational readRational();
        std::string readFunc();
};
#endif // READER_H
