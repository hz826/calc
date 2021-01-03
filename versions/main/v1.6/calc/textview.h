#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <QQuickWindow>
#include <QtCore/QObject>

/* textview.h
 *
 * 对 QML 中 Text 控件的封装
 */

class TextView
{
public:
    TextView(QObject * p);
    void setText(QString s);

private:
    QObject * text;
};

#endif // TEXTVIEW_H
