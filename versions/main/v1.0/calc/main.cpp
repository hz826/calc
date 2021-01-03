#include <QtCore/qglobal.h>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include "listener.h"
#include "renderer.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<Listener>("Tooska", 1, 0, "Listener");
    qmlRegisterType<Renderer>("Tooska", 1, 0, "Renderer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    /*********************************/

    Listener * pL = engine.rootObjects().first()->findChild<Listener *>("m_listener");
    Renderer * pR = engine.rootObjects().first()->findChild<Renderer *>("m_renderer");
    //pR->Refresh("123456");
    pL->init_link(pR);
    /*********************************/

    return app.exec();
}
