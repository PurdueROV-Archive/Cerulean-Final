#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>

#include "main.h"
#include "controller.h"
#include "model.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Controller* control = new Controller();
    engine.rootContext()->setContextProperty("controller", control);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    Model* model = new Model();
    model->init(control);

    return app.exec();
}
