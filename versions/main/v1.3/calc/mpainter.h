#ifndef MPAINTER_H
#define MPAINTER_H

#include <QQuickPaintedItem>
#include <QQuickWindow>
#include <QPainter>
#include <QTimer>
#include <QtMath>
#include <QDebug>
#include "box.h"

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
    void queryText(QString s,int size,int &w,int &h);
    void drawText(QString s,int size,int x,int y);

    Box* getBox(QString s,int size);
    void solve(int size);

    const int m_TimeInterval = 700;
    const double Ascent_Alpha = 0.75, Descent_Alpha = 0.55;

    QString text;
    QPainter *n_painter;
    int m_TimerId;
    bool showCursor;
};

#endif // MPAINTER_H
