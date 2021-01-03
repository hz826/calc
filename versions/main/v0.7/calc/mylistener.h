#ifndef MYLISTENER_H
#define MYLISTENER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Mylistener : public QObject
{
    Q_OBJECT
public:
    explicit Mylistener(QObject *parent = 0);

public slots:
    void sendkey(QString key);
};

#endif // MYLISTENER_H
