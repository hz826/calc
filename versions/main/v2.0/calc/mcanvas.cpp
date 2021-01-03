#include "mcanvas.h"

mCanvas::mCanvas(QQuickItem *parent) : QQuickPaintedItem (parent) {
    //m_TimerId = startTimer(m_TimeInterval);
    text = "|";
}

mCanvas::~mCanvas() {
    //if (m_TimerId != 0) killTimer(m_TimerId);
}

void mCanvas::timerEvent(QTimerEvent *event) {
    (void)event;
    update();
}

void mCanvas::Refresh(QString newtext) {
    qDebug() << "Refresh : " << newtext << endl;
    text = newtext;
    showCursor = true;

    update();
    //if (m_TimerId != 0) killTimer(m_TimerId);
    //m_TimerId = startTimer(m_TimeInterval);
}

void mCanvas::paint(QPainter *painter) {
    mpainter.setPainter(painter);

    QString exception = Renderer(text,18).get(0,200);
    if (exception != "") {
        qDebug() << "Error ! " + exception << endl;
    }

    showCursor = !showCursor;
    mpainter.freePainter();
}
