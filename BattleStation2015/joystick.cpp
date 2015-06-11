#include "joystick.h"

Joystick::Joystick() : QObject() {
    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
        qDebug() << SDL_GetError();
     }
}

QStringList Joystick::joystickList() {
    SDL_JoystickUpdate();

    deviceList.clear();

    for(int i = 0; i < SDL_NumJoysticks(); i++) {
        QString info = QString(SDL_JoystickNameForIndex(i));
        qDebug() << info;
        if (!info.isEmpty()) {
            deviceList.append(info);
        }
    }

    return deviceList;
}

bool Joystick::select(int id) {
    return true;
}

bool Joystick::init() {
    return true;
}

void Joystick::disconnect() {

}

Joystick::~Joystick() {

}

