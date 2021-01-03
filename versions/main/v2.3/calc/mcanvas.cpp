#include "mcanvas.h"

mCanvas::mCanvas(QQuickItem *parent) : QQuickPaintedItem (parent) {
    m_TimerId = startTimer(m_TimeInterval);
    text = "|";
    update();
}

mCanvas::~mCanvas() {
    if (m_TimerId != 0) killTimer(m_TimerId);
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
    if (m_TimerId != 0) killTimer(m_TimerId);
    m_TimerId = startTimer(m_TimeInterval);
}

void mCanvas::paint(QPainter *painter) {//不能直接调用paint()，应该调用update()函数
    mpainter.setPainter(painter);

    try {
        cursor_position.clear();
        Renderer(text,18).get(5,200,cursor_position,showCursor);
    } catch (const char* exception) {
        qDebug() << "renderer: Error ! " + QString(exception) << endl;
    }
    showCursor = !showCursor;

    //for (QPoint &p : cursor_position) painter->drawEllipse(p,3,3);

    mpainter.freePainter();
}
