#include "mcanvas.h"

mCanvas::mCanvas(QQuickItem *parent) : QQuickPaintedItem (parent) {
    text = "|";
    m_TimerId = 0;
    modified = false;
    mode = FREE;
    cursor_num = 0;
    cursor_pos = new QPoint [1];
    box = new Box();
    box_ans = new Box();
}

mCanvas::~mCanvas() {
    if (m_TimerId != 0) killTimer(m_TimerId);
}

void mCanvas::timerEvent(QTimerEvent *event) {
    (void)event;
    update();
}

void mCanvas::Refresh(QString text,QString expr,QString ans) {
    this->text = text;
    this->expr = expr;
    this->ans = ans;

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
            qDebug() << "Update : " << text << endl;

            delete [] cursor_pos;
            cursor_num = 0;
            for(int i=0;i<text.length();i++) if (text[i] == '$' || text[i] == '|') ++cursor_num;
            cursor_pos = new QPoint[cursor_num];
            modified = false;

            delete box;
            delete box_ans;

            qDebug() << "Expr.toTeX() = " << expr << endl;
            box = Renderer(text,18).get();
            box_ans = Renderer(expr,14).get();
            box->draw(5,box->hu+15,cursor_pos,showCursor);
            box_ans->draw(960-box_ans->w,250-box_ans->hd,NULL,false);
            mode = FREE;
        } else {
            box->draw(5,box->hu+15,NULL,showCursor);
            box_ans->draw(960-box_ans->w,250-box_ans->hd,NULL,false);
        }

        int ans_w, ans_h;
        mpainter.Query(ans,14,ans_w,ans_h);
        mpainter.Text(ans,14,980-ans_w,290-ans_h);

        //painter->drawEllipse(5,15,3,3);
    } catch (const char* exception) {
        qDebug() << "renderer: Error ! " + QString(exception) << endl;
    }
    showCursor = !showCursor;

    //for (QPoint &p : cursor_position) painter->drawEllipse(p,3,3);
    mpainter.freePainter();
}
