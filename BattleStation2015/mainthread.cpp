#include "mainthread.h"

MainThread::MainThread(Serial* serial, Joystick* joystick1, Joystick* joystick2) : QObject() {
    this->serial = serial;
    this->joystick1 = joystick1;
    this->joystick2 = joystick2;

    this->controller = Controller::getInstance();
}

MainThread::~MainThread() {

}

bool MainThread::start() {

    threadTimer = new QTimer(0);

    threadTimer->setTimerType(Qt::PreciseTimer);
    threadTimer->setInterval(TICK_INTERVAL);

    //Connect thredTimer timeout to tick slot
    connect(threadTimer, SIGNAL(timeout()), SLOT(tick()), Qt::DirectConnection);

    qDebug() << "Starting thread";
    if (serial->connect()) {
        qDebug() << "Serial connected!";
     } else {
        qDebug() << "No serial?";
        return false;
    }

    if (joystick1->connect()) {
        qDebug() << "Main Joystick connected";
    } else {
        return false;
    }

//    if (joystick2->connect()) {
//        qDebug() << "Secondary Joystick connected";
//    }

    threadTimer->start();
    return true;
}


void MainThread::stop() {
    qDebug() << "Stopping loop";
    serial->stop();
    joystick1->disconnect();
    if (joystick2->isConnected()) joystick2->disconnect();

    if (threadTimer) {
        threadTimer->stop();
        delete threadTimer;
    }
}


void MainThread::tick() {

    qint64 now = QDateTime::currentMSecsSinceEpoch();
    //qDebug() << (now - lastTime);
    lastTime = now;

    if (serial && joystick1->isConnected()) {

        joystick1->update();

        ControlPacket* cPacket = new ControlPacket();

        //Emergency Stop Feature (Home Button)
        if (joystick1->getButtonPressed(JOYSTICK_HOME)) {
            homeHeldTime = 1;
        }

        if (joystick1->getButtonState(JOYSTICK_HOME) && homeHeldTime > 0) {
            homeHeldTime++;
        } else {
            homeHeldTime = 0;
        }

        if (homeHeldTime > ((1000/TICK_INTERVAL) * 0.75)) {
            controller->modelStopRunning();
            stop();
        }


        //Camera Toggles (Y and B)
        if (joystick1->getButtonPressed(JOYSTICK_Y)) {
            controller->modelToggleCameraSelect1();
            qDebug() << controller->modelGetCameraSelect1();
        }

        cPacket->setCamMux1(controller->modelGetCameraSelect1());


        if (joystick1->getButtonPressed(JOYSTICK_B)) {
            controller->modelToggleCameraSelect2();
        }

        cPacket->setCamMux2(controller->modelGetCameraSelect2());


        //Laser Off (R3)
        if (joystick1->getButtonPressed(JOYSTICK_R3)) {
            controller->modelLaserOff();
        }
        cPacket->setLaser(controller->modelLaserEnabled());


        //Stepper Control (DPAD)
        if (joystick1->getButtonState(JOYSTICK_DP_LEFT)) {
            cPacket->setHStepper(false, 2);
        }

        if (joystick1->getButtonState(JOYSTICK_DP_RIGHT)) {
            cPacket->setHStepper(true, 2);
        }

        if (joystick1->getButtonState(JOYSTICK_DP_UP)) {
            cPacket->setVStepper(true, 2);
        }

        if (joystick1->getButtonState(JOYSTICK_DP_DOWN)) {
            cPacket->setVStepper(false, 2);
        }

        //LED Control
        quint8 leds[5] = {
            controller->modelLEDValue(1),
            controller->modelLEDValue(2),
            controller->modelLEDValue(3),
            controller->modelLEDValue(4),
            controller->modelLEDValue(5)
        };

        cPacket->setLEDs(leds);

        //Calculate Thruster Values

        //Y (Ascend and descend)
        int velY = joystick1->getAxis(JOYSTICK_RTRIGG) - joystick1->getAxis(JOYSTICK_LTRIGG);

        //X (Strafe left and right)
        int velX = 0;
        if (joystick1->getButtonState(JOYSTICK_LEFTBUTTON)) velX += -1000;
        if (joystick1->getButtonState(JOYSTICK_RIGHTBUTTON)) velX += 1000;

        //Z (forward and backword)
        int velZ = joystick1->getAxis(JOYSTICK_LJ_Y);

        //Yaw (rotate clockwise and counter-clockwise)
        int yaw = joystick1->getAxis(JOYSTICK_LJ_X);

        //Pitch (rotate forward and backward)
        int pitch = joystick1->getAxis(JOYSTICK_RJ_Y);

        //Roll (rotate left to right)
        int roll = joystick1->getAxis(JOYSTICK_RJ_X);

        //Calculate Limits
        int horizontalLimit = controller->modelGetThrusterGroupScale("horizontal");
        velZ = (int) (velZ * (horizontalLimit/100.0));
        yaw  = (int) (yaw  * (horizontalLimit/100.0));

        int verticalLimit = controller->modelGetThrusterGroupScale("vertical");
        velY = (int) (velY * (verticalLimit/100.00));

        int strafeLimit = controller->modelGetThrusterGroupScale("stafe");
        velX = (int) (velX * (strafeLimit/100.00));

        int pitchRollLimit = controller->modelGetThrusterGroupScale("pitchroll");
        pitch  = (int) (pitch  * (pitchRollLimit/100.0));
        roll   = (int) (roll   * (pitchRollLimit/100.0));

        int thrusters[8] = {0,0,0,0,0,0,0,0};
        int* horizontalThrusters = thrusters;
        int* verticalThrusters = thrusters + 4;

        horizontalThrusters[0] += velX;
        horizontalThrusters[1] -= velX;
        horizontalThrusters[2] += velX;
        horizontalThrusters[3] -= velX;

        verticalThrusters[0] += velY;
        verticalThrusters[1] += velY;
        verticalThrusters[2] += velY;
        verticalThrusters[3] += velY;

        horizontalThrusters[0] += velZ;
        horizontalThrusters[1] += velZ;
        horizontalThrusters[2] -= velZ;
        horizontalThrusters[3] -= velZ;

        verticalThrusters[0] += pitch;
        verticalThrusters[1] += pitch;
        verticalThrusters[2] -= pitch;
        verticalThrusters[3] -= pitch;

        horizontalThrusters[0] -= yaw;
        horizontalThrusters[1] += yaw;
        horizontalThrusters[2] += yaw;
        horizontalThrusters[3] -= yaw;

        verticalThrusters[0] += roll;
        verticalThrusters[1] -= roll;
        verticalThrusters[2] += roll;
        verticalThrusters[3] -= roll;

        Thruster::normalize(horizontalThrusters, 4);
        Thruster::normalize(verticalThrusters, 4);

        for (int i = 0; i < 8; ++i) {
            cPacket->setThruster(i+1, Thruster::convert(thrusters[i]));
        }







        cPacket->print();
        serial->write(cPacket->getPacket());
        delete cPacket;

//        QByteArray status = serial->read();
//        if (status.size() > 0) {
//            qDebug() << "Data read";
//            for (int i = 0; i < status.size(); i++) {
//                qDebug("[%d]: [%d]: %c", i, status.at(i), status.at(i));
//            }
//        }
    }

}
