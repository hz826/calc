#ifndef OUTPUT_H
#define OUTPUT_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QtQml/QQmlApplicationEngine>

class myTextView {
private:
    QObject * p;
public:
    bool init(QObject * ptr);
    bool setText(QString s);
};

#endif // OUTPUT_H
