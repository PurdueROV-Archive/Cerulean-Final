#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"
#include <QString>

class Motor
{

public:
    Motor(quint8 address, QString type);
    ~Motor();

    void set(quint8 speed, quint8 direction);
    quint8 get();

    quint8 getDirection();
    quint8 getSpeed();

    quint8 getAddress();

private:
    quint8 m_address;
    QString m_type;
    quint8 m_speed;
    quint8 m_direction;

    void setSpeed(quint8 speed);
    void setDirection(quint8 direction);
};

#endif // MOTOR_H
