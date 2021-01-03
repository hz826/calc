#include "mpainter.h"

mPainter::mPainter(QQuickItem *parent) : QQuickPaintedItem (parent) {
    //m_TimerId = startTimer(m_TimeInterval);
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
    //if (m_TimerId != 0) killTimer(m_TimerId);
    //m_TimerId = startTimer(m_TimeInterval);
}

void mPainter::drawText(QString s, int size, int x, int y) {//(x,y) 左上角
    if (n_painter == NULL) {
        qDebug() << "n_painter is NULL!" << endl;
    }
    QFont font("Microsoft YaHei", size, 0);
    n_painter->setFont(font);
    QFontMetrics metrics = n_painter->fontMetrics();

    y += metrics.ascent() * Renderer::Ascent_Alpha;
    n_painter->drawText(x, y, s);
}

void mPainter::paint(QPainter *painter) {
    n_painter = painter;
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(qRgba(120, 110, 250, 250)));
    painter->drawRect(QRect(0,0,1000,300));

    Renderer Ren(text,painter,20);
    QString exception = Ren.get();
    if (exception != "") {
        qDebug() << "Error ! " + Ren.exception << endl;
    }

    showCursor = !showCursor;
    n_painter = NULL;
}
