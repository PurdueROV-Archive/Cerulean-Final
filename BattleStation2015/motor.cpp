#include "motor.h"

Motor::Motor(quint8 address, QString type) {
    if (address == 0) throw 1;
    this->m_address = address;

    if (type.isEmpty()) throw 2;

    this->m_type = "type";
}


void Motor::set(quint8 speed, quint8 direction) {
    setSpeed(speed);
    setDirection(direction);
}

quint8 Motor::get() {
    quint8 val = 0x00;
    val = (this->getSpeed() >> 1);

    if (this->getDirection() == 1) {
        val = val & 0x80;
    }

    return val;
}

quint8 Motor::getAddress() {
    return this->m_address;
}

quint8 Motor::getDirection() {
    return this->m_direction;
}

quint8 Motor::getSpeed() {
    return this->m_speed;
}


void Motor::setSpeed(quint8 speed) {
    this->m_speed = speed;
}

void Motor::setDirection(quint8 direction) {
    this->m_direction = (direction == 0) ? 0 : 1;
}


Motor::~Motor() {

}
