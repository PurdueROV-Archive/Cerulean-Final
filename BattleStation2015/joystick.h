#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include "sdlwrap.h"
#include "SDL.h"
#undef main

#define INT_16_MAX 32767
#define INT_16_MIN 32768

struct ButtonState {
    bool lastState;
    bool currentState;
};



class Joystick : public QObject
{
    Q_OBJECT

public:
    explicit Joystick();
    ~Joystick();

    bool select(int index);
    bool connect();

    void disconnect();

    bool isConnected();

    int getNumAxes();
    int getNumButtons();

    bool getButtonState(int buttonId);

    bool getButtonPressed(int buttonId);
    bool getButtonReleased(int buttonId);

    qint32 getAxis(int axisId);

    void update();


private:
    bool connected;

    int numAxes;
    int numButtons;

    QList<ButtonState> buttons;

    QList<qint16> axes;
    QList<qint16> axesZero;

    QString joystickName;

    int joystickId;
    SDL_Joystick* sdlJoystick;



signals:

public slots:

};

#endif // JOYSTICK_H
