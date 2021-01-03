#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <QQuickWindow>
#include <QtCore/QObject>

class TextView
{
public:
    TextView(QObject * p);
    void setText(QString s);

private:
    QObject * text;
};

#endif // TEXTVIEW_H
