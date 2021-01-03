#include "mylistener.h"


Mylistener::Mylistener(QObject *parent) : QObject(parent)
{
    QMetaObject::connectSlotsByName(this);
}

void Mylistener::sendkey(QString key)
{

}
