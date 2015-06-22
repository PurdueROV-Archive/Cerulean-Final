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

    Controller* control = Controller::getInstance();
    engine.rootContext()->setContextProperty("controller", control);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    qRegisterMetaType<Sint16>("Sint16");

    Model* model = new Model();
    model->init();

    return app.exec();
}
