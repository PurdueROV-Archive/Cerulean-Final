#include "model.h"


Model::Model() : QObject() {

}

void Model::init(Controller* controller) {
    this->controller = controller;
    QObject::connect(this->controller, &Controller::modelRefreshSerial,
                     this, &Model::refreshSerial);

    QObject::connect(this->controller, &Controller::modelSelectSerial,
                     this, &Model::selectSerial);

    QObject::connect(this->controller, &Controller::modelStart,
                     this, &Model::start);

    QObject::connect(this->controller, &Controller::modelStop,
                         this, &Model::stop);

    serial = new Serial();
    controller->modelSetSerialDevices(serial->serialDevices());
}

Model::~Model() {

}

void Model::refreshSerial() {
    controller->modelSetSerialDevices(serial->serialDevices());
}

void Model::selectSerial(int index) {
    serial->select(index);
}

void Model::start() {
    qDebug() << "Starting in model";
    if (serial->connect()) {
        qDebug() << "Serial connected!";
        for (int i = 0; i < 2048; i++) {
            serial->write("A");
        }

        ControlPacket* cPacket = new ControlPacket();
        cPacket->print();
        serial->write(cPacket->getPacket());


    } else {
        controller->modelStopRunning();
    }
}

void Model::stop() {
    qDebug() << "Stopping";
    serial->stop();
}
