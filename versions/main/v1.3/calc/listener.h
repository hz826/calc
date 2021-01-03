#ifndef LISTENER_H
#define LISTENER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "mpainter.h"
#include "textview.h"

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

private:
    mPainter * pmPainter;
    TextView * pTextView;
    QString text;
    void BeforeModify();
    void AfterModify();
};

#endif // LISTENER_H
