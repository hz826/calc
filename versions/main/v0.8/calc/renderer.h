#ifndef RENDERER_H
#define RENDERER_H

#include <QQuickPaintedItem>

struct Point
{
    QPoint point;
    int alpha;

    Point(const QPoint &p, int a) : point(p) , alpha(a) { }
};

class Renderer : public QQuickPaintedItem
{
    Q_OBJECT

public:
    Renderer(QQuickItem *parent = nullptr);
    ~Renderer();

    Q_INVOKABLE void start();
    void timerEvent(QTimerEvent *event) override;

protected:
    virtual void paint(QPainter *painter) override;

private:
    bool m_drawable = false;
    int m_angle = 0;
    QList<Point> m_points;
    QTimer *m_updateTimer;
    int mCurrent = 0;
};


#endif // RENDERER_H
