#ifndef MODEL_H
#define MODEL_H

#include <QObject>

#include "main.h"
#include "controller.h"
#include "controlpacket.h"
#include "serial.h"

class Model : public QObject
{
    Q_OBJECT

public:
    Model();
    ~Model();

    void init(Controller* controller);

private:
    bool initialized;
    Serial* serial;

    Controller* controller;

public slots:
    void refreshSerial();
    void selectSerial(int index);
    void start();
    void stop();

};

#endif // MODEL_H
