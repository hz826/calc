#ifndef CANVAS_H
#define CANVAS_H

#include <QPainter>
#include <QDebug>
#include <QtMath>

/* canvas.h
 *
 * canvas 是用于自定义 QPainter 绘图的 class, 有一个全局 canvas
 * Query 返回字符串宽、高
 * Height 返回字符串高
 * Text 绘制字符串
 * Line 绘制直线
 *
 * mPainter 的 paint() 函数在开始时传递 QPainter 指针, 在结束时销毁指针
 */

class Canvas {
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

extern Canvas canvas;

#endif // CANVAS_H
