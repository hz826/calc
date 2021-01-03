#include "mpainter.h"

mPainter::mPainter(QQuickItem *parent) : QQuickPaintedItem (parent) {
    m_TimerId = startTimer(m_TimeInterval);
    text = "|";
}

mPainter::~mPainter() {
    //if (m_TimerId != 0) killTimer(m_TimerId);
}

void mPainter::timerEvent(QTimerEvent *event) {
    (void)event;
    update();
}

void mPainter::Refresh(QString newtext) {
    qDebug() << "Refresh : " << newtext << endl;
    this->text = newtext;
    showCursor = true;

    update();
    if (m_TimerId != 0) killTimer(m_TimerId);
    m_TimerId = startTimer(m_TimeInterval);
}

void mPainter::queryText(QString s, int size, int &w, int &h) {
    if (n_painter == NULL) {
        qDebug() << "n_painter is NULL!" << endl;
    }
    QFont font("Microsoft YaHei", size, 0);
    n_painter->setFont(font);
    QFontMetrics metrics = n_painter->fontMetrics();

    w = metrics.horizontalAdvance(s);
    h = metrics.ascent() * Ascent_Alpha + metrics.descent() * Descent_Alpha;
}

void mPainter::drawText(QString s, int size, int x, int y) {//(x,y) 左上角
    if (n_painter == NULL) {
        qDebug() << "n_painter is NULL!" << endl;
    }
    QFont font("Microsoft YaHei", size, 0);
    n_painter->setFont(font);
    QFontMetrics metrics = n_painter->fontMetrics();

    y += metrics.ascent() * Ascent_Alpha;
    n_painter->drawText(x, y, s);
}

Box* mPainter::getBox(QString s,int size) {
    int w, h;
    queryText(s, size, w, h);
    return new Box(s, size, w, h);
}

void mPainter::paint(QPainter *painter) {
    n_painter = painter;
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(qRgba(120, 110, 250, 250)));
    painter->drawRect(QRect(0,0,1000,300));

    QString s = "test+";
    int x = 150, y = 50, w, h, siz = 60;
    queryText(s, siz, w, h);
    drawText(s, siz, x, y);
    QRect r(x,y,w,h);
    painter->drawRect(r);
    painter->drawEllipse(x,y,5,5);
    painter->drawLine(x,y+h/2,x+w,y+h/2+1);

    showCursor = !showCursor;
    n_painter = NULL;
}
