#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "main.h"


class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool Running READ Running WRITE SetRunning NOTIFY RunningChanged())
    Q_PROPERTY(QStringList SerialDevices READ SerialDevices NOTIFY SerialDevicesChanged)


/////////////////////////////////////////
//  Class (de)Contsructor Definitions  //
/////////////////////////////////////////
public:
    explicit Controller();
    ~Controller();


/////////////////////////////////////////
//  Control Thread Running Properties  //
/////////////////////////////////////////

public:
    bool Running() const; //Read property

    void SetRunning(bool running); //Write Property

private: //Dependencies
    bool running;

signals: //Signal to emit on change
    void RunningChanged();

//Model C++ Control Methods
public:
    void modelStopRunning(); //set running to false

signals:
    void modelStart(); //signal for start connection
    void modelStop(); //signal for stop connection


/////////////////////////////////////////
//     Serial Control Properties       //
/////////////////////////////////////////

//QML Property Definitions
public:
    QStringList SerialDevices() const; //Read property

    //Write Property

private: //Dependencies
    QStringList serialDevices;

signals: //Signal to emit on change
    void SerialDevicesChanged();

//Additional Control Methods
public slots:

    //Select a device based combo index
    void SerialSelect(int index);

    //Refresh device list
    void RefreshSerial();

private: //dependencies
    int index; //Selected Serial Device Index

//Model C++ Control Methods
public:
    //set serial device qlist for combobox
    void modelSetSerialDevices(QStringList serialDevices);

signals:
    void modelRefreshSerial(); //emit to refresh serial qlist
    void modelSelectSerial(int index); //emit when serial device combobox index changed


/////////////////////////////////////////
//     Thruster Control Properties     //
/////////////////////////////////////////
//QML Property Definitions
public:
    //Read property

    //Write Property

private: //Dependencies


signals: //Signal to emit on change


//Additional Control Methods
public slots:

    //Set scaling factor
    void ThrusterControlScale(int address, int value);


private: //dependencies
    quint8 thrusterControl[8];


/////////////////////////////////////////
//         Misc Public Slots           //
/////////////////////////////////////////
public slots:
    void doSomething();

};

#endif // CONTROLLER_H
