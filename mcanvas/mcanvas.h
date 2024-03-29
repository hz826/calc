#ifndef MCANVAS_H
#define MCANVAS_H

#include <QQuickPaintedItem>
#include <QQuickWindow>
#include <QPainter>
#include <QTimer>
#include <QtMath>
#include <QDebug>
#include "renderer.h"

/* mcanvas.h
 *
 * 注入到 QML 中的绘图类
 * 由系统调用 paint() 函数实现绘图
 *
 * 可设置timer定时重绘实现光标闪烁, 也可手动调用 update() 重绘
 * Listener 调用 Refresh 更新信息
 */

class mCanvas : public QQuickPaintedItem {
    Q_OBJECT

public:
    mCanvas(QQuickItem *parent = nullptr);
    ~mCanvas();
    void timerEvent(QTimerEvent *event) override;
    void Refresh(QString text,QString expr,QString ans);

    QPoint *cursor_pos;
    int cursor_num;

    enum {READ, WRITE, FREE} mode;

protected:
    virtual void paint(QPainter *painter) override;

private:
    Box * box, *box_ans;
    static constexpr int m_TimeInterval = 700;
    QString text, expr, ans;
    int m_TimerId;
    bool showCursor;
    bool modified;
};

#endif // MCANVAS_H
