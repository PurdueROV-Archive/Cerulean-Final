#include "mainthread.h"

MainThread::MainThread(Serial* serial, Joystick* joystick1, Joystick* joystick2) : QObject() {
    this->serial = serial;
    this->joystick1 = joystick1;
    this->joystick2 = joystick2;
}

MainThread::~MainThread() {

}

bool MainThread::start() {

    threadTimer = new QTimer(0);

    threadTimer->setTimerType(Qt::PreciseTimer);
    threadTimer->setInterval(TICK_INTERVAL);

    //Connect thredTimer timeout to tick slot
    connect(threadTimer, SIGNAL(timeout()), SLOT(tick()), Qt::DirectConnection);

    qDebug() << "Starting thread";
    if (serial->connect()) {
        qDebug() << "Serial connected!";
     } else {
        return false;
    }

    if (joystick1->connect()) {
        qDebug() << "Main Joystick connected";
    } else {
        return false;
    }

//    if (joystick2->connect()) {
//        qDebug() << "Secondary Joystick connected";
//    }

    threadTimer->start();
    return true;
}


void MainThread::stop() {
    qDebug() << "Stopping loop";
    serial->stop();
    joystick1->disconnect();
    if (joystick2->isConnected()) joystick2->disconnect();

    if (threadTimer) {
        threadTimer->stop();
        delete threadTimer;
    }
}


void MainThread::tick() {

    qint64 now = QDateTime::currentMSecsSinceEpoch();
    qDebug() << (now - lastTime);
    lastTime = now;

    if (serial) {
        ControlPacket* cPacket = new ControlPacket();

        if (joystick1->getButtonState(2)) {
            cPacket->setHStepper(false, 2);
        }

        if (joystick1->getButtonState(3)) {
            qDebug() << "RIIIGTH";
            cPacket->setHStepper(true, 2);
        }

        if (joystick1->getButtonState(0)) {
            cPacket->setVStepper(true, 2);
        }

        if (joystick1->getButtonState(1)) {
            cPacket->setVStepper(false, 2);
        }

        cPacket->print();
        serial->write(cPacket->getPacket());
        delete cPacket;

        QByteArray status = serial->read();
        if (status.size() > 0) {
            qDebug() << "Data read";
            for (int i = 0; i < status.size(); i++) {
                qDebug("[%d]: [%d]: %c", i, status.at(i), status.at(i));
            }
        }
    }

    if (joystick1 && joystick1->isConnected()) {
        joystick1->update();
        for (int i = 0; i < joystick1->getNumAxes(); i++) {
            //qDebug("Joystick 1: Axis %d val %d", i, joystick1->getAxis(i));
        }
    }

   if (joystick2 && joystick2->isConnected()) {
        joystick2->update();
        for (int i = 0; i < joystick2->getNumAxes(); i++) {
            //qDebug("Joystick 2: Axis %d val %d", i, joystick2->getAxis(i));
        }
    }




}

