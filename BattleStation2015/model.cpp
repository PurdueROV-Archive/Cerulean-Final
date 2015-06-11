#include "model.h"


Model::Model() : QObject() {
    running = false;
}

void Model::init(Controller* controller) {
    this->controller = controller;

    QObject::connect(this->controller, &Controller::modelRefreshList,
                     this, &Model::refreshList);

    QObject::connect(this->controller, &Controller::modelSelectSerial,
                     this, &Model::selectSerial);

    QObject::connect(this->controller, &Controller::modelStart,
                     this, &Model::start);

    QObject::connect(this->controller, &Controller::modelStop,
                         this, &Model::stop);

    serial = new Serial();
    controller->modelSetSerialDevices(serial->serialDevices());

    joystick1 = new Joystick();
    joystick2 = new Joystick();

    controller->modelSetJoystickDevices(joystick1->joystickList());

    qThread = new QThread(this);
    mainThread = new MainThread(serial);
}

Model::~Model() {
    if (serial) delete serial;
    if (mainThread) delete mainThread;
    if (qThread) delete qThread;

}

void Model::refreshList() {
    controller->modelSetSerialDevices(serial->serialDevices());
    controller->modelSetJoystickDevices(joystick1->joystickList());
}

void Model::selectSerial(int index) {
    serial->select(index);
}

void Model::start() {
    running = true;
    if (mainThread->start()) {
        running = true;
    } else {
        running = false;
        emit controller->modelStopRunning();
    }
}

void Model::stop() {
    running = false;
    mainThread->stop();
}
