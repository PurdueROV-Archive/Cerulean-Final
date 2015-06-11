#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include "SDL.h"
#undef main

class Joystick : public QObject
{
    Q_OBJECT

public:
    explicit Joystick();
    ~Joystick();

    QStringList joystickList();

    bool select(int id);
    bool init();

    void disconnect();


private:
    bool connected;

    QStringList deviceList;

    int joystickId;
    SDL_Joystick* sdlJoystick;



signals:

public slots:

};

#endif // JOYSTICK_H
