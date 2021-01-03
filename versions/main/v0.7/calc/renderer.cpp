#include "renderer.h"

#include <QQuickWindow>
#include <QPainter>
#include <QTimer>
#include <QtMath>

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
    mCurrent =(mCurrent + 3) % 360;
    update();
}

void Renderer::paint(QPainter *painter)
{
    static bool flag = true;
    if (flag) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(qRgba(120, 110, 250, 250)));

    //格子
    for(int i = 0; i < width(); i += 20)
        painter->drawLine(i + 0.5, 0, i + 0.5, height());
    for(int j = 0; j < height(); j += 20)
        painter->drawLine(0, j + 0.5, width(), j + 0.5);

    /*if (false)
    {
        int diff = int(qAbs(width() - height()) / 2);
        QConicalGradient gradient(width() / 2, height() / 2, m_angle + 180);
        gradient.setColorAt(0.1, QColor(15, 45, 188, 200));
        gradient.setColorAt(0.7, QColor(15, 45, 188, 0));
        painter->setBrush(gradient);
        painter->setPen(QPen(Qt::NoPen));
        if (width() > height())
            painter->drawPie(diff, 0, min, min, m_angle * 16, 60 * 16);
        else painter->drawPie(0, diff, min, min, m_angle * 16, 60 * 16);

        for(int i = 0; i < 5; ++i)
        {
            painter->setBrush(QBrush(QColor(15, 45, 188, m_points.at(i).alpha)));
            painter->drawEllipse(m_points.at(i).point, 7, 7);
        }
        m_angle -= 2;
    }*/
    flag = false;
    } else {
        int min = int(qMin(width(), height()));
        QPoint center(int(width() / 2), int(height() / 2));
        painter->drawEllipse(center, min / 2, min / 2);
        painter->drawEllipse(center, min / 3, min / 3);
        painter->drawEllipse(center, min / 6, min / 6);
    }
}
