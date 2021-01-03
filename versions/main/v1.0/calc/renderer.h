#ifndef RENDERER_H
#define RENDERER_H

#include <QQuickPaintedItem>
#include <QQuickWindow>
#include <QPainter>
#include <QTimer>
#include <QtMath>
#include <QDebug>

class Renderer : public QQuickPaintedItem
{
    Q_OBJECT

public:
    Renderer(QQuickItem *parent = nullptr);
    ~Renderer();
    void timerEvent(QTimerEvent *event) override;
    void Refresh(QString newtext);

protected:
    virtual void paint(QPainter *painter) override;

private:
    const int m_TimeInterval = 700;

    QString text;
    int m_TimerId;
    bool showCursor;
};


#endif // RENDERER_H
