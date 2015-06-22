#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMutex>

#include "main.h"


class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool Running READ Running WRITE SetRunning NOTIFY RunningChanged())

    Q_PROPERTY(QStringList SerialDevices READ SerialDevices NOTIFY SerialDevicesChanged)

    Q_PROPERTY(QStringList JoystickDevices READ JoystickDevices NOTIFY JoystickDevicesChanged)

    Q_PROPERTY(bool CameraSelect1 READ CameraSelect1 WRITE SetCameraSelect1 NOTIFY CameraSelect1Changed)
    Q_PROPERTY(bool CameraSelect2 READ CameraSelect2 WRITE SetCameraSelect2 NOTIFY CameraSelect2Changed)

    Q_PROPERTY(bool LaserEnabled READ LaserEnabled WRITE SetLaserEnabled NOTIFY LaserEnabledChanged)
    Q_PROPERTY(int LaserDistance READ LaserDistance NOTIFY LaserDistanceChanged)


/////////////////////////////////////////
// Class & (de)Contsructor Definitions //
/////////////////////////////////////////
public:
    static Controller* getInstance();

private:
    Controller() {};
    Controller(Controller const&);
    void operator=(Controller const&);
    ~Controller();

    static Controller* instance;
    static QMutex mutex;


/////////////////////////////////////////
//  Control Thread Running Properties  //
/////////////////////////////////////////

public:
    bool Running() const; //Read property

    void SetRunning(bool running); //Write Property

private: //Dependencies
    bool running = false;

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

private: //dependencies
    int index; //Selected Serial Device Index

//Model C++ Control Methods
public:
    //set serial device qlist for combobox
    void modelSetSerialDevices(QStringList serialDevices);

signals:
    void modelSelectSerial(int index); //emit when serial device combobox index changed


/////////////////////////////////////////
//     Joystick Control Properties     //
/////////////////////////////////////////

//QML Property Definitions
public:
    QStringList JoystickDevices() const; //Read property

    //Write Property

private: //Dependencies
    QStringList joystickDevices;

signals: //Signal to emit on change
    void JoystickDevicesChanged();

//Additional Control Methods
public slots:

    //Select a device based combo index
    void Joystick1Select(int index);
    void Joystick2Select(int index);

private: //dependencies
    int joystick1Index; //Selected Serial Device Index
    int joystick2Index;

//Model C++ Control Methods
public:
    //set serial device qlist for combobox
    void modelSetJoystickDevices(QStringList joystickDevices);

signals:
    void modelJoystick1Select(int index); //emit when serial device combobox index changed
    void modelJoystick2Select(int index); //emit when serial device combobox index changed


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
    //Set scale factor for groups
    void ThrusterScaleGroups(QString group, int value);


private: //dependencies
    quint8 thrusterControl[8] = {100, 100, 100, 100, 100, 100, 100, 100};
    quint8 groupFactor[4] = {100, 100, 100, 100};

public:
    quint8 modelGetThrusterGroupScale(QString group);
    quint8 modelThrusterScale(int address);

/////////////////////////////////////////
//      Camera Select Properties       //
/////////////////////////////////////////

//QML Property Definitions
public:
    //Read property
    bool CameraSelect1() const;
    bool CameraSelect2() const;

    //Write Property
    void SetCameraSelect1(bool cameraSelect1);
    void SetCameraSelect2(bool cameraSelect2);

private: //Dependencies
    bool cameraSelect1 = false;
    bool cameraSelect2 = false;

signals: //Signal to emit on change
    void CameraSelect1Changed();
    void CameraSelect2Changed();


//Model C++ Control Methods
public:
    //set serial device qlist for combobox
    void modelToggleCameraSelect1();
    void modelToggleCameraSelect2();

    bool modelGetCameraSelect1();
    bool modelGetCameraSelect2();


/////////////////////////////////////////
//          Laser Properties           //
/////////////////////////////////////////

//QML Property Definitions
public:
    //Read Property
    bool LaserEnabled() const; //Read property
    int LaserDistance() const;

    //Write Property
    void SetLaserEnabled(bool enabled);

private: //Dependencies
    bool laserEnabled = false;
    quint16 laserDistance = 0;

signals: //Signal to emit on change
    void LaserEnabledChanged();
    void LaserDistanceChanged();

//Model C++ Control Methods
public:
    //set serial device qlist for combobox
    void modelLaserOff();
    bool modelLaserEnabled();
    void modelSetLaserDistance(quint16 distance);

/*
/////////////////////////////////////////
//       Bilge Pump Properties         //
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

private: //dependencies
    int index; //Selected Serial Device Index

//Model C++ Control Methods
public:
    //set serial device qlist for combobox
    void modelSetSerialDevices(QStringList serialDevices);

signals:
    void modelSelectSerial(int index); //emit when serial device combobox index changed

/////////////////////////////////////////
//      Fuse Detection Properties      //
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

private: //dependencies
    int index; //Selected Serial Device Index

//Model C++ Control Methods
public:
    //set serial device qlist for combobox
    void modelSetSerialDevices(QStringList serialDevices);

signals:
    void modelSelectSerial(int index); //emit when serial device combobox index changed

/////////////////////////////////////////
//   Voltage Measurement Properties    //
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

private: //dependencies
    int index; //Selected Serial Device Index

//Model C++ Control Methods
public:
    //set serial device qlist for combobox
    void modelSetSerialDevices(QStringList serialDevices);

signals:
    void modelSelectSerial(int index); //emit when serial device combobox index changed
*/

/////////////////////////////////////////
//       Laser Control Properties      //
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
    void LEDControlScale(int address, int value);


private: //dependencies
    quint8 ledControl[5] = {0,0,0,0,0};

//Model C++ Control Methods
public:
    //set serial device qlist for combobox
    quint8 modelLEDValue(int address);

/////////////////////////////////////////
//         Misc Public Slots           //
/////////////////////////////////////////
public slots:
    void doSomething();
    void RefreshLists();

signals:
    void modelRefreshList(); //emit to refresh serial qlist

};
#endif // CONTROLLER_H
