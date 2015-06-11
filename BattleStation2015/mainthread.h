#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QObject>
#include <QDateTime>

#include "main.h"
#include "serial.h"
#include "controlpacket.h"
#include <QTimer>

//Tick Interval: 10ms (100Hz)
#define TICK_INTERVAL 10

class MainThread : public QObject
{

    Q_OBJECT

public:
    explicit MainThread(Serial* serial);
    ~MainThread();

private:
    Serial* serial;
    QTimer* threadTimer;
    QThread* mainThread;

public slots:
    void tick();
    bool start();
    void stop();

};

#endif // MAINTHREAD_H
