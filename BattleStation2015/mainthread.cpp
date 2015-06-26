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
    //qDebug() << now-lastTime;

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

        //Claw Control
        if (joystick1->getButtonPressed(JOYSTICK_A)) {
            clawState = !clawState;
        }

        cPacket->setClaw(clawState);

        //Bilge Pump Control
        cPacket->setBilgePump(controller->modelGetBilgePumpEnabled());


        //Stepper Control (DPAD & X)
        if (joystick1->getButtonPressed(JOYSTICK_X)) {
            stepperAngle = 0;
            controller->modelSetStepperAngle(0);
        }

        if (joystick1->getButtonState(JOYSTICK_DP_LEFT)) {
            cPacket->setHStepper(false, 1);
            stepperAngle -= 1;
            controller->modelSetStepperAngle(stepperAngle);
        }

        if (joystick1->getButtonState(JOYSTICK_DP_RIGHT)) {
            cPacket->setHStepper(true, 1);
            stepperAngle += 1;
            controller->modelSetStepperAngle(stepperAngle);
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

        //Valve Turner
        int valveValue = controller->modelGetValveValue();
        if (valveValue != 0) {
            bool neg = valveValue < 0;
            valveValue = (int) ((abs(valveValue)-1) * (600/9)) + 400;
            valveValue = (neg) ? valveValue*-1 : valveValue;
        }

        cPacket->setFootTurner(Thruster::convert(valveValue));

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

        int diff = 25;
        for (int i = 0; i < 8; i++) {
            if (abs(thrusters[i] - lastThrusters[i]) > diff) {
                if (lastThrusters[i] < thrusters[i]) {
                    thrusters[i] = lastThrusters[i] + diff;
                } else if (lastThrusters[i] > thrusters[i]) {
                    thrusters[i] = lastThrusters[i] - diff;
                }
            }
            lastThrusters[i] = thrusters[i];
        }

//        qDebug("[1]: %d, [2]: %d, [3]: %d, [4]: %d\n[5]: %d, [6]: %d, [7]: %d, [8]: %d",
//               horizontalThrusters[0], horizontalThrusters[1], horizontalThrusters[2], horizontalThrusters[3],
//                verticalThrusters[0], verticalThrusters[1], verticalThrusters[2], verticalThrusters[3]);

        for (int i = 0; i < 8; ++i) {
            cPacket->setThruster(i+1, Thruster::convert(thrusters[i]));
        }

        controller->modelSetThrusterValues(thrusters);


        //cPacket->print();
        serial->write(cPacket->getPacket());
        delete cPacket;

        QByteArray status = serial->read();
        if (status.size() > 0) {
            qDebug() << "Data read";
            for (int i = 0; i < status.size(); i++) {
                qDebug("[%d]: %d", i, (quint8) status.at(i));
            }

            if (status.size() >= 13) {
                quint16 voltage1 = 0x00;
                voltage1 |= status.at(2) << 8;
                voltage1 |= status.at(3);

                quint16 voltage2 = 0x00;
                voltage2 |= status.at(4) << 8;
                voltage2 |= status.at(5);

                quint16 voltage3 = 0x00;
                voltage3 |= status.at(6) << 8;
                voltage3 |= status.at(7);

                controller->modelSetVoltageDevice(voltage1, voltage2, voltage3);


                quint32 laser = 0x00;
                quint8 laser1 = status.at(7);
                quint8 laser2 = status.at(8);
                quint8 laser3 = status.at(9);
                quint8 laser4 = status.at(10);
                laser |= (laser1 << 24);
                laser |= (laser2 << 16);
                laser |= (laser3 <<  8);
                laser |= laser4;

                float laserMeasurement = laser * 1.0;
                laserMeasurement -= 10000;
                laserMeasurement *= 1.33;
                laserMeasurement += 5000;
                laserMeasurement /= 1000;
                controller->modelSetLaserDistance(laserMeasurement);

            }
        }
    }

}
