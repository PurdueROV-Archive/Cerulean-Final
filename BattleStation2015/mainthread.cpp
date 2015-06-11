#include "mainthread.h"

MainThread::MainThread(Serial* serial) : QObject() {
    this->serial = serial;
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
        threadTimer->start();
        return true;
    } else {
        return false;
    }

}


void MainThread::stop() {
    qDebug() << "Stopping loop";
    serial->stop();

    if (threadTimer) {
        threadTimer->stop();
        delete threadTimer;
    }
}


void MainThread::tick() {

    if (serial) {
        ControlPacket* cPacket = new ControlPacket();
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
}

