#include "model.h"


Model::Model() : QObject() {
    running = false;
}

void Model::init() {
    this->controller = Controller::getInstance();

    QObject::connect(this->controller, &Controller::modelRefreshList,
                     this, &Model::refreshList);

    QObject::connect(this->controller, &Controller::modelSelectSerial,
                     this, &Model::selectSerial);

    QObject::connect(this->controller, &Controller::modelJoystick1Select,
                     this, &Model::selectJoystick1);

    QObject::connect(this->controller, &Controller::modelJoystick2Select,
                     this, &Model::selectJoystick2);

    QObject::connect(this->controller, &Controller::modelStart,
                     this, &Model::start);

    QObject::connect(this->controller, &Controller::modelStop,
                         this, &Model::stop);

    serial = new Serial();
    controller->modelSetSerialDevices(serial->serialDevices());

    if (SdlWrap::init() == false) {
        qDebug() << SdlWrap::getError();
    }

    controller->modelSetJoystickDevices(SdlWrap::getJoystickList());

    joystick1 = new Joystick();
    joystick2 = new Joystick();

    qThread = new QThread(this);
    mainThread = new MainThread(serial, joystick1, joystick2);
}

Model::~Model() {
    if (serial) delete serial;
    if (mainThread) delete mainThread;
    if (qThread) delete qThread;

}

void Model::refreshList() {
    controller->modelSetSerialDevices(serial->serialDevices());
    controller->modelSetJoystickDevices(SdlWrap::getJoystickList());
}

void Model::selectSerial(int index) {
    serial->select(index);
}

void Model::selectJoystick1(int index) {
    joystick1->select(index);
}

void Model::selectJoystick2(int index) {
    joystick2->select(index);
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
