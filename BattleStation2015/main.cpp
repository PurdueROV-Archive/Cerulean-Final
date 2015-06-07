#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>

#include "main.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Controller* control = new Controller();
    engine.rootContext()->setContextProperty("controller", control);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
