#include "controller.h"

//Controller::Controller() : QObject() {
//    //Make sure it isn't running to begin with
//    running = false;
//}

Controller* Controller::instance = NULL;
QMutex Controller::mutex;

Controller* Controller::getInstance() {
    QMutexLocker locker(&mutex);

    if (instance == NULL) {
        instance = new Controller();
    }

    return instance;
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
    if (index < 0) return;
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
//     Joystick Control Properties     //
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

QStringList Controller::ThrusterValues() {
    return thrusterValues;
}


/////////////////////////////////////////
//          Thruster Control           //
/////////////////////////////////////////


//Control Methods
void Controller::ThrusterControlScale(int address, int value) {
    if (value < 0 || value > 100) return;
    if (address < 1 || address > 8) return;

    thrusterControl[address-1] = value;
    qDebug("Set thruster %d to max %d", address, value);
}

void Controller::ThrusterScaleGroups(QString group, int value) {
    if (value < 0 || value > 100) return;

    if (group == "horizontal") {
        groupFactor[0] = value;
        return;
    } else if (group == "vertical") {
        groupFactor[1] = value;
        return;
    } else if (group == "strafe") {
        groupFactor[2] = value;
        return;
    } else if (group == "pitchroll") {
        groupFactor[3] = value;
        return;
    }
}

quint8 Controller::modelGetThrusterGroupScale(QString group) {
    if (group == "horizontal") {
        return groupFactor[0];
    } else if (group == "vertical") {
        return groupFactor[1];
    } else if (group == "strafe") {
        return groupFactor[2];
    } else if (group == "pitchroll") {
        return groupFactor[3];
    }

    return 100;
}

quint8 Controller::modelThrusterScale(int address) {
    if (address < 1 || address > 8) return 100;
    return thrusterControl[address-1];
}

void Controller::modelSetThrusterValues(int values[]) {
    thrusterValues.clear();
    QString val;
    for (int i = 0; i < 8; i++) {
       val = QString("%1").arg(values[i]/10);
       thrusterValues.append(val + "%");
    }
    emit ThrusterValuesChanged();
}

/////////////////////////////////////////
//      Camera Select Properties       //
/////////////////////////////////////////


//Read property
bool Controller::CameraSelect1() const {
    return cameraSelect1;
}
bool Controller::CameraSelect2() const {
    return cameraSelect2;
}

//Write Property
void Controller::SetCameraSelect1(bool cameraSelect1) {
    this->cameraSelect1 = cameraSelect1;
    emit CameraSelect1Changed();
}

void Controller::SetCameraSelect2(bool cameraSelect2) {
    this->cameraSelect2 = cameraSelect2;
    emit CameraSelect2Changed();
}


//Model C++ Control Methods
void Controller::modelToggleCameraSelect1() {
    bool newCamera = !this->cameraSelect1;
    SetCameraSelect1(newCamera);
}

void Controller::modelToggleCameraSelect2() {
    bool newCamera = !this->cameraSelect2;
    SetCameraSelect2(newCamera);
}

bool Controller::modelGetCameraSelect1() {
    return cameraSelect1;
}

bool Controller::modelGetCameraSelect2() {
    return cameraSelect2;
}


/////////////////////////////////////////
//          Laser Properties           //
/////////////////////////////////////////


bool Controller::LaserEnabled() const {
    return laserEnabled;
}

float Controller::LaserDistance() const {
    return laserDistance;
}

void Controller::SetLaserEnabled(bool enabled) {
    laserEnabled = enabled;
    emit LaserEnabledChanged();
}

void Controller::modelLaserOff() {
    laserEnabled = false;
    emit LaserEnabledChanged();
}

bool Controller::modelLaserEnabled() {
    return laserEnabled;
}

void Controller::modelSetLaserDistance(float distance) {
    laserDistance = distance;
    emit LaserDistanceChanged();
}

/////////////////////////////////////////
//         LED Control Properties      //
/////////////////////////////////////////

//Control Methods
void Controller::LEDControlScale(int address, int value) {
    if (value < 0 || value > 100) return;
    if (address < 1 || address > 5) return;

    float pwm = 2.55 * value;

    ledControl[address-1] = (int) pwm;
}

quint8 Controller::modelLEDValue(int address) {
    if (address < 1 || address > 5) return 0;

    return ledControl[address-1];
}

/////////////////////////////////////////
//            Valve Turner             //
/////////////////////////////////////////

void Controller::ValveValue(int value) {
    this->value = value;
}

int Controller::modelGetValveValue() {
    return value;
}

/////////////////////////////////////////
//       Bilge Pump Properties         //
/////////////////////////////////////////

bool Controller::BilgePumpEnabled() const {
    return bilgePumpEnabled;
}

void Controller::SetBilgePumpEnabled(bool enabled) {
    bilgePumpEnabled = enabled;
    emit BilgePumpEnabledChanged();
}

bool Controller::modelGetBilgePumpEnabled() {
    return bilgePumpEnabled;
}

/////////////////////////////////////////
//       Voltage Properties            //
/////////////////////////////////////////

int Controller::Voltage1() const {
    return voltage1measure;
}

int Controller::Voltage2() const {
    return voltage2measure;
}

int Controller::Voltage3() const {
    return voltage3measure;
}

void Controller::modelSetVoltageDevice(int voltage1, int voltage2, int voltage3) {
    this->voltage1measure = voltage1;
    this->voltage2measure = voltage2;
    this->voltage3measure = voltage3;
    emit Voltage1Changed();
    emit Voltage2Changed();
    emit Voltage3Changed();
}

/////////////////////////////////////////
//      Stepper Angle Properties       //
/////////////////////////////////////////

float Controller::StepperAngle() const {
    return angle * 0.9;
}

void Controller::modelSetStepperAngle(int angle) {
    this->angle = angle;
    emit StepperAngleChanged();
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



