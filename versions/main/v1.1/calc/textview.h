#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "renderer.h"

class TextView
{
public:
    explicit TextView(QObject * p);
    void setText(QString s);

private:
    QObject * text;
};

#endif // TEXTVIEW_H
