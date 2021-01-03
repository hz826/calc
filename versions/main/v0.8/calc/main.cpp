#include <QtCore/qglobal.h>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include "mylistener.h"
#include "output.h"
#include "renderer.h"

myTextView debug;

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<Mylistener>("Tooska", 1, 0, "Mylistener");
    qmlRegisterType<Renderer>("Tooska", 1, 0, "Renderer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    /*********************************/

    debug.init(engine.rootObjects().first()->findChild<QObject *>("debug"));
    debug.setText("Hello!");

    return app.exec();
}
