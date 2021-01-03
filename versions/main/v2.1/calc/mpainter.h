#ifndef MPAINTER_H
#define MPAINTER_H

#include <QPainter>
#include <QDebug>
#include <QtMath>

/* mpanter.h
 *
 * 是对QPainter的封装
 * Query 返回字符串宽、高
 * Height 返回字符串高
 * Text 绘制字符串
 * Line 绘制直线
 *
 * mCanvas 的 paint() 函数在开始时传递 QPainter 指针, 在结束时销毁指针
 */

class mPainter {
private:
    QPainter *painter;
    static constexpr double Ascent_Alpha = 0.75, Descent_Alpha = 0.55;

public:
    void Query(QString s, int size, int &w, int &h);
    int Height(int size);

    void Text(QString s, int size, int x, int y);//(x,y) 左上角
    void Line(int x,int y,int xx,int yy);

    void setPainter(QPainter *mpainter);
    void freePainter();
};

extern mPainter mpainter;

#endif // MPAINTER_H
