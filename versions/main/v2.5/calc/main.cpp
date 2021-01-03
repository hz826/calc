#include <QtCore/qglobal.h>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include "listener.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<Listener>("TeamWuhanAlice", 1, 0, "Listener");
    qmlRegisterType<mCanvas>("TeamWuhanAlice", 1, 0, "MCanvas");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    /*********************************/

    Listener * pL = engine.rootObjects().first()->findChild<Listener *>("m_listener");
    mCanvas * pC = engine.rootObjects().first()->findChild<mCanvas *>("m_canvas");
    QObject * pT1 = engine.rootObjects().first()->findChild<QObject *>("answer");
    QObject * pT2 = engine.rootObjects().first()->findChild<QObject *>("status");

    pL->init_link(pC,pT1,pT2);
    /*********************************/

    return app.exec();
}
