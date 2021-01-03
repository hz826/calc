#include <QtCore/qglobal.h>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include "listener.h"
#include "mpainter.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<Listener>("TeamWuhanAlice", 1, 0, "Listener");
    qmlRegisterType<mPainter>("TeamWuhanAlice", 1, 0, "MPainter");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    /*********************************/

    Listener * pL = engine.rootObjects().first()->findChild<Listener *>("m_listener");
    mPainter * pP = engine.rootObjects().first()->findChild<mPainter *>("m_painter");
    QObject * pT = engine.rootObjects().first()->findChild<QObject *>("answer");
    pT->setProperty("text","!");

    pL->init_link(pP,pT);
    /*********************************/

    return app.exec();
}
