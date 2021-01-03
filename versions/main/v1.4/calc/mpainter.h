#ifndef MPAINTER_H
#define MPAINTER_H

#include <QQuickPaintedItem>
#include <QQuickWindow>
#include <QPainter>
#include <QTimer>
#include <QtMath>
#include <QDebug>
#include "renderer.h"

class mPainter : public QQuickPaintedItem {
    Q_OBJECT

public:
    mPainter(QQuickItem *parent = nullptr);
    ~mPainter();
    void timerEvent(QTimerEvent *event) override;
    void Refresh(QString newtext);

protected:
    virtual void paint(QPainter *painter) override;

private:
    void drawText(QString s,int size,int x,int y);

    static constexpr int m_TimeInterval = 700;
    QString text;
    QPainter *n_painter;
    int m_TimerId;
    bool showCursor;
};

#endif // MPAINTER_H
