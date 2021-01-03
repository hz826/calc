#ifndef RENDERER_H
#define RENDERER_H

#include <QPainter>
#include <QDebug>
#include <QtMath>
#include "box.h"

/* renderer.h
 *
 * 数学渲染器
 * 解析字符串, 转换为数学书写
 * get函数以(x,y)为原点绘制
 */

class Renderer {
private:
    class Reader {
    private:
        QString text;
        QChar at(int );
        int index;
    public:
        Reader(QString text);
        QChar ext();
        void getnxt();
        void getlast();
        bool match(QString s);
        QString debug();
    } R;

    int cursorid;
    int defaultSize;
    int lower(int size);//字号缩小一号
    int difference(int w1,int w2);//

    Box* readFunction(int size);
    Box* readBracket(int size, QChar L, QChar R);
    Box* read(int size);

    void draw(Box *box,int x,int y,bool showCursor);
public:
    Renderer(QString text,int defaultSize);
    void get(int x,int y,QVector<QPoint> &cursor,bool showCursor);
};

#endif // RENDERER_H
