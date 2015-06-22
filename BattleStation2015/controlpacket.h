#ifndef CONTROLPACKET_H
#define CONTROLPACKET_H

#include "main.h"
#include "motor.h"

#include <QByteArray>

#define PACKET_SIZE 20

#define HEADER 0x12
#define TAIL 0x13

#define CONTROL 0x01

#define CRC_BYTE 0xC5

#define THRUSTER_BYTE_START 1

#define FOOT_TURNER 9

#define TOOLS 10

#define STEPPER 11

#define LED_START 12

#define THRUSTER_COUNT 8

#define LED_COUNT 5


class ControlPacket
{
public:
    ControlPacket();
    ~ControlPacket();

    void setThrusters(Motor** motors);

    void setThruster(int address, quint8 value);

    void setFootTurner(Motor* motor);

    void setCamMux1(bool camMux1);

    void setCamMux2(bool camMux2);

    void setBilgePump(bool suck, bool push);

    void setVoltageMeasurement(bool enabled);

    void setLaser(bool enabled);

    void setClaw(bool open, bool close);

    void setLEDs(quint8 values[5]);

    void setVStepper(bool upDirection, quint8 value);

    void setHStepper(bool rightDirection, quint8 value);


    QByteArray getPacket();

    void reset();

    void print();


private:
    quint8 size;
    QByteArray data;


    quint8 thrusterValues[THRUSTER_COUNT];
    quint8 footTurner;

    bool camMux1;
    bool camMux2;

    bool bilgePumpSuck;
    bool bilgePumpPush;

    bool voltageMeasurement;

    bool laser;

    bool clawOpening;
    bool clawClosing;

    bool vStepperUpDirection;
    quint8 vStepperAmount;

    bool hStepperRightDirection;
    quint8 hStepperAmount;

    quint8 ledValues[LED_COUNT];

    quint8 getToolByte();

    quint8 getStepperByte();

    void assemblePacket();

    quint8 crc(QByteArray data);

};

#endif // CONTROLPACKET_H
