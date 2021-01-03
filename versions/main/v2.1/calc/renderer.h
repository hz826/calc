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
        int index;
        QChar at(int i);
    public:
        Reader(QString text);
        QChar next();
        void getnxt();
        bool match(QString s);
    } R;

    int defaultSize;
    int lower(int size);
    int center(int w1,int w2);

    Box* readFunction(int size);
    Box* readBracket(int size, QChar L, QChar R);
    Box* read(int size);

    void draw(Box *box,int x,int y);
public:
    Renderer(QString text,int defaultSize);
    void get(int x,int y);
};

#endif // RENDERER_H
