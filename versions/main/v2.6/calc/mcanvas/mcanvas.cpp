#include "mcanvas.h"

mCanvas::mCanvas(QQuickItem *parent) : QQuickPaintedItem (parent) {
    text = "|";
    m_TimerId = 0;
    modified = false;
    mode = FREE;
    cursor_num = 0;
    cursor_pos = new QPoint [1];
    box = new Box();
}

mCanvas::~mCanvas() {
    if (m_TimerId != 0) killTimer(m_TimerId);
}

void mCanvas::timerEvent(QTimerEvent *event) {
    (void)event;
    update();
}

void mCanvas::Refresh(QString newtext) {
    //qDebug() << "Refresh : " << newtext << endl;
    text = newtext;
    showCursor = true;
    modified = true;

    update();
    if (m_TimerId != 0) killTimer(m_TimerId);
    m_TimerId = startTimer(m_TimeInterval);
}

void mCanvas::paint(QPainter *painter) {//不能直接调用paint()，应该调用update()函数
    mpainter.setPainter(painter);

    try {
        if (modified && mode == FREE) {
            mode = WRITE;

            delete [] cursor_pos;
            cursor_num = 0;
            for(int i=0;i<text.length();i++) if (text[i] == '$' || text[i] == '|') ++cursor_num;
            cursor_pos = new QPoint[cursor_num];
            modified = false;

            delete box;
            box = Renderer(text,18).get();
            box->draw(5,200,cursor_pos,showCursor);
            mode = FREE;
        } else {
            box->draw(5,200,NULL,showCursor);
        }
    } catch (const char* exception) {
        qDebug() << "renderer: Error ! " + QString(exception) << endl;
    }
    showCursor = !showCursor;

    //for (QPoint &p : cursor_position) painter->drawEllipse(p,3,3);
    mpainter.freePainter();
}
