#ifndef LISTENER_H
#define LISTENER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "mpainter.h"
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
    void init_link(mPainter * pP, QObject *pT);

public slots:
    void sendkey(QString key);
    void left();
    void right();
    void home();
    void end();
    void clear();
    void test();//debug 用

private:
    mPainter * pmPainter;
    TextView * pTextView;
    QString text;
    void BeforeModify();
    void AfterModify();
};

#endif // LISTENER_H
