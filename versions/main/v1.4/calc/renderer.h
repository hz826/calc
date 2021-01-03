#ifndef RENDERER_H
#define RENDERER_H

#include <QPainter>
#include <QDebug>
#include <QtMath>
#include "box.h"

class Renderer {
private:
    class Reader {
    private:
        QString text;
        int index;
        QChar at(int i);
    public:
        Reader(QString text);
        QChar next();
        void getnxt();
        bool match(QString s);
    } R;

    QPainter * painter;
    int defaultSize;
    bool halt;

    void Halt(QString E);

    int Max(int x,int y);
    int Min(int x,int y);
    int lower(int size);
    int center(int w1,int w2);

    void queryText(QString s,int size,int &w,int &h);
    int getDefaultHeight(int size);
    Box* getBox(QString s,int size);

    Box* readFunction(int size);
    Box* readBracket(int size, QChar L, QChar R);
    Box* read(int size);
public:
    static constexpr double Ascent_Alpha = 0.75, Descent_Alpha = 0.55;
    Renderer(QString text,QPainter *painter,int defaultSize);
    QString get();
    QString exception;
    Box* result;
};

#endif // RENDERER_H
