#include "controller.h"

Controller::Controller() : QObject() {
    //Make sure it isn't running to begin with
    running = false;
}

Controller::~Controller() {

}


/////////////////////////////////////////
//  Control Thread Running Properties  //
/////////////////////////////////////////

//Read property
bool Controller::Running() const {
    return running;
}

//Write Property
void Controller::SetRunning(bool running) {
    this->running = running;

    if (this->running) {
        emit modelStart();
    } else {
        emit modelStop();
    }

    emit RunningChanged();
}

//set running to false, from model
void Controller::modelStopRunning() {
    running = false;
    emit RunningChanged();
}

/////////////////////////////////////////
//     Serial Control Properties       //
/////////////////////////////////////////

//Read Property
QStringList Controller::SerialDevices() const {
    return serialDevices;
}

//Additional Control Methods

//Select a device
void Controller::SerialSelect(int index) {
    this->index = index;
    emit modelSelectSerial(this->index);
}

//Model C++ Control Methods

//set serial device qlist for combobox
void Controller::modelSetSerialDevices(QStringList serialDevices) {
    qDebug() << "Setting new devices";
    this->serialDevices = serialDevices;
    emit SerialDevicesChanged();
}

/////////////////////////////////////////
//     Serial Control Properties       //
/////////////////////////////////////////

//Read Property
QStringList Controller::JoystickDevices() const {
    return joystickDevices;
}

//Additional Control Methods

//Select a device
void Controller::Joystick1Select(int index) {
    joystick1Index = index;
    emit modelJoystick1Select(joystick1Index);
}

//Select a device
void Controller::Joystick2Select(int index) {
    joystick2Index = index;
    emit modelJoystick2Select(joystick2Index);
}


//Model C++ Control Methods

//set serial device qlist for combobox
void Controller::modelSetJoystickDevices(QStringList joystickDevices) {
    qDebug() << "Setting new joystick";
    this->joystickDevices = joystickDevices;
    emit JoystickDevicesChanged();
}


/////////////////////////////////////////
//          Thruster Control           //
/////////////////////////////////////////


//Control Methods
void Controller::ThrusterControlScale(int address, int value) {
    if (value < 0 || value > 100) return;
    if (address < 1 || address > 8) return;

    this->thrusterControl[address-1] = value;
    qDebug("Set thruster %d to max %d%", address, value);
}


/////////////////////////////////////////
//         Misc Public Slots           //
/////////////////////////////////////////

//Test C++ function
void Controller::doSomething() {
    qDebug() << "Testing!";
}

//Refresh Serial Devices
void Controller::RefreshLists() {
    emit modelRefreshList();
}



