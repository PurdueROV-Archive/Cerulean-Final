#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDateTime>

#include "main.h"
#include "mainthread.h"
#include "controller.h"
#include "controlpacket.h"
#include "joystick.h"
#include "serial.h"

class Model : public QObject
{
    Q_OBJECT

public:
    Model();
    ~Model();

    void init(Controller* controller);

private:
    bool running;

    Serial* serial;
    Joystick* joystick1;
    Joystick* joystick2;

    Controller* controller;
    MainThread* mainThread;

    QThread* qThread;

public slots:
    void refreshList();
    void selectSerial(int index);
    void start();
    void stop();

};

#endif // MODEL_H
