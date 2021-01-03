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

void mPainter::paint(QPainter *painter) {
    canvas.setPainter(painter);

    QString exception = Renderer(text,18).get(0,200);
    if (exception != "") {
        qDebug() << "Error ! " + exception << endl;
    }

    showCursor = !showCursor;
    canvas.freePainter();
}
