#include "mpainter.h"

mPainter mpainter;

void mPainter::Query(QString s, int size, int &w, int &h) {
    if (painter == NULL) return ;

    QFont font("Microsoft YaHei", size, 0);
    painter->setFont(font);
    QFontMetrics metrics = painter->fontMetrics();

    w = metrics.horizontalAdvance(s);
    h = metrics.ascent() * Ascent_Alpha + metrics.descent() * Descent_Alpha;
}

int mPainter::Height(int size) {
    if (painter == NULL) return 0;
    int w, h;
    Query("|", size, w, h);
    return h;
}

void mPainter::Text(QString s, int size, int x, int y) {//(x,y) 左上角
    if (painter == NULL) return ;

    QFont font("Microsoft YaHei", size, 0);
    painter->setFont(font);
    QFontMetrics metrics = painter->fontMetrics();

    y += metrics.ascent() * Ascent_Alpha;
    painter->drawText(x, y, s);
}

void mPainter::Line(int x,int y,int xx,int yy) {
    if (painter == NULL) return ;
    painter->drawLine(x,y,xx,yy);
}

void mPainter::setPainter(QPainter *mpainter) {
    painter = mpainter;
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(qRgba(120, 110, 250, 250)));
    painter->drawRect(QRect(0,0,1000,300));
    //painter->drawLine(QLine(0,100,1000,100));  // baseline
}

void mPainter::freePainter() {
    painter = NULL;
}
