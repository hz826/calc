#ifndef LISTENER_H
#define LISTENER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "mcanvas.h"
#include "textview.h"

/* listener.h
 *
 * 接受事件并处理(虚拟按键/键盘/鼠标)
 * 维护光标
 */

class Listener : public QObject
{
    Q_OBJECT
public:
    explicit Listener(QObject * parent = 0);
    ~Listener();
    void init_link(mCanvas * pC, QObject *pT1, QObject *pT2);

public slots:
    void onclick(int x,int y);
    void sendkey(QString key);
    void backspace();
    void left();
    void right();
    void home();
    void end();
    void clear();
    void calc();
    void test();//debug 用

private:
    mCanvas * pCanvas;
    TextView * pTAnswer, * pTStatus;
    QString text;
    void BeforeModify();
    void AfterModify();
};

#endif // LISTENER_H
