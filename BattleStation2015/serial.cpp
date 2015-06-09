#include "serial.h"

Serial::Serial() {
    device = new QSerialPort();
    serialDevices();
}

Serial::~Serial() {
    if (device) delete device;
}


QStringList Serial::serialDevices() {

    serialDevicesList.clear();
    serialDeviceInfo.clear();

    QList<QSerialPortInfo> serialPortInfo = QSerialPortInfo::availablePorts();

    foreach(const QSerialPortInfo &info, serialPortInfo){
        if (info.isBusy() == false) {
            QString device = info.description() + ", " + info.portName();
            serialDevicesList.append(device);
            serialDeviceInfo.append(info);
        }
    }

    return serialDevicesList;
}

void Serial::select(int index) {

    QSerialPortInfo deviceInfo = serialDeviceInfo.at(index);

    qDebug() << "Selecting " << deviceInfo.description() << ", " << deviceInfo.portName();

    device->setPort(deviceInfo);
    device->setBaudRate(BAUD_RATE);
}

bool Serial::connect() {
    if (device) {
        return device->open(QIODevice::ReadWrite);
    } else {
        return false;
    }

}

void Serial::stop() {
    if (device->isOpen()) device->close();
}

bool Serial::write(char* byte) {
    if (device->isWritable()) {
        device->write(byte);
        return device->flush();
    }
}

bool Serial::write(QByteArray data) {
    if (device->isWritable()) {
        device->write(data);
        return device->flush();
    }
}

