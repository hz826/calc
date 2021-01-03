#include "renderer.h"

Renderer::Renderer(QQuickItem *parent) : QQuickPaintedItem (parent) {
    m_TimerId = startTimer(m_TimeInterval);
    text = "$";
}

Renderer::~Renderer() {
    //if (m_TimerId != 0) killTimer(m_TimerId);
}

void Renderer::timerEvent(QTimerEvent *event) {
    (void)event;
    update();
}

void Renderer::Refresh(QString newtext) {
    qDebug() << "Refresh : " << newtext << endl;
    this->text = newtext;
    showCursor = true;

    update();
    if (m_TimerId != 0) killTimer(m_TimerId);
    m_TimerId = startTimer(m_TimeInterval);
}

void Renderer::queryText(QPainter *painter,QString s, int size, int &w, int &h) {
    QFont font("Microsoft YaHei", size, 0);
    painter->setFont(font);
    QFontMetrics metrics = painter->fontMetrics();

    w = metrics.horizontalAdvance(s);
    h = metrics.ascent() * Ascent_Alpha + metrics.descent() * Descent_Alpha;
}

void Renderer::drawText(QPainter *painter,QString s, int size, int x, int y) {
    //(x,y) 左上角
    QFont font("Microsoft YaHei", size, 0);
    painter->setFont(font);
    QFontMetrics metrics = painter->fontMetrics();

    y += metrics.ascent() * Ascent_Alpha;
    painter->drawText(x, y, s);
}

void Renderer::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(qRgba(120, 110, 250, 250)));
    painter->drawRect(QRect(0,0,1000,300));

    QString s = "test+";
    int x = 150, y = 50, w, h, siz = 60;
    queryText(painter, s, siz, w, h);
    drawText(painter, s, siz, x, y);
    QRect r(x,y,w,h);
    painter->drawRect(r);
    painter->drawEllipse(x,y,5,5);
    painter->drawLine(x,y+h/2,x+w,y+h/2+1);

    showCursor = !showCursor;
}
