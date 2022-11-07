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

    pL->init_link(pC);
    /*********************************/

    return app.exec();
}
