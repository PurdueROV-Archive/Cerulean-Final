#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QObject>
#include <QDateTime>

#include "main.h"
#include "serial.h"
#include "controlpacket.h"
#include "joystick.h"
#include "controller.h"
#include "thruster.h"
#include <QTimer>

//Tick Interval: 10ms (100Hz)
#define TICK_INTERVAL 100

class MainThread : public QObject
{

    Q_OBJECT

public:
    explicit MainThread(Serial* serial, Joystick* joystick1, Joystick* joystick2);
    ~MainThread();

private:
    Serial* serial;

    Joystick* joystick1;
    Joystick* joystick2;

    Controller* controller;

    QTimer* threadTimer;
    QThread* mainThread;

    qint64 lastTime = QDateTime::currentMSecsSinceEpoch();

    qint16 homeHeldTime = 0;

public slots:
    void tick();
    bool start();
    void stop();

};

#endif // MAINTHREAD_H
