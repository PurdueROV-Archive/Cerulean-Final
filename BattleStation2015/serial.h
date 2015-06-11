#ifndef SERIAL_H
#define SERIAL_H


#include <main.h>

#include <QStringList>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#define BAUD_RATE 115200


class Serial
{
public:
    Serial();
    ~Serial();

    QStringList serialDevices();

    void select(int index);
    bool connect();
    void stop();

    bool isOpen();

    bool write(char* byte);
    bool write(QByteArray data);

    QByteArray read();

private:
    QStringList serialDevicesList;
    QList<QSerialPortInfo> serialDeviceInfo;

    QSerialPort* device;

};

#endif // SERIAL_H
