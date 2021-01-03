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

void Renderer::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(qRgba(120, 110, 250, 250)));

    QFont font("Microsoft YaHei", 60, 0);
    painter->setFont(font);

    QString s = text;
    if (!showCursor) s.replace("$","");
    //s.append(cnt);
    painter->drawText(0, 200, s);
    //++cnt;
/*
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
    painter->drawRect(rr);*/
    showCursor = !showCursor;
}
