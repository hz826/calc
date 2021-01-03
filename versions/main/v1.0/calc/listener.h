#ifndef LISTENER_H
#define LISTENER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "renderer.h"

class Listener : public QObject
{
    Q_OBJECT
public:
    explicit Listener(QObject * parent = 0);
    void init_link(Renderer * pR);

public slots:
    void sendkey(QString key);
    void left();
    void right();
    void home();
    void end();
    void clear();

private:
    Renderer * pRenderer;
    //QObject * pTextView;
    QString text;
    void BeforeModify();
    void AfterModify();
};

#endif // LISTENER_H
