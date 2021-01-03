#include "renderer.h"

#include <QQuickWindow>
#include <QPainter>
#include <QTimer>
#include <QtMath>
#include <QDebug>

Renderer::Renderer(QQuickItem *parent) : QQuickPaintedItem (parent)
{
    startTimer(1000);
}

Renderer::~Renderer()
{

}

void Renderer::start() {

}

void Renderer::timerEvent(QTimerEvent *event)
{
    (void)event;
    update();
}

void Renderer::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(qRgba(120, 110, 250, 250)));

    QFont font("Microsoft YaHei", 60, 0);
    painter->setFont(font);

    QString s1 = "123中文", s2 = "def";

    QFontMetrics metrics = painter->fontMetrics();
    int x = 30, y = 50;
    painter->drawEllipse(x,y,100,100);

    int yy = y + metrics.ascent();
    painter->drawText(x, yy, s1+s2);

    QRect r(x,y,metrics.horizontalAdvance(s1),metrics.height());
    qDebug() << r << endl;
    painter->drawRect(r);
    QRect rr(x+metrics.horizontalAdvance(s1),y,metrics.horizontalAdvance(s2),metrics.height());
    qDebug() << rr << endl;
    painter->drawRect(rr);
    /*
    static bool flag = true;
    if (flag) {
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(QPen(qRgba(120, 110, 250, 250)));

        //格子
        for(int i = 0; i < width(); i += 20)
            painter->drawLine(i + 0.5, 0, i + 0.5, height());
        for(int j = 0; j < height(); j += 20)
            painter->drawLine(0, j + 0.5, width(), j + 0.5);
        flag = false;
    } else {
        int min = int(qMin(width(), height()));
        QPoint center(int(width() / 2), int(height() / 2));
        painter->drawEllipse(center, min / 2, min / 2);
        painter->drawEllipse(center, min / 3, min / 3);
        painter->drawEllipse(center, min / 6, min / 6);
    }*/
}
