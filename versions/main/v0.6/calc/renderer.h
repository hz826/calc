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

protected:
    virtual void paint(QPainter *painter);

private:
    bool m_drawable = false;
    int m_angle = 0;
    QList<Point> m_points;
    QTimer *m_updateTimer;
};


#endif // RENDERER_H
