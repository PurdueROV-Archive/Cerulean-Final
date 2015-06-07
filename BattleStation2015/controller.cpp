#include "controller.h"

Controller::Controller() : QObject() {

}

bool Controller::running() const {
    return m_running;
}

void Controller::setRunning(bool running) {
    m_running = running;
    emit runningChanged();
}

void Controller::doSomething() {
    qDebug() << "Testing!";
}

void Controller::thrusterControlMax(int address, int value) {
    if (value < 0 || value > 100) return;
    if (address < 1 || address > 8) return;

    this->thrusterControl[address-1] = value;
    qDebug("Set thruster %d to max %d%", address, value);
}

Controller::~Controller() {

}
