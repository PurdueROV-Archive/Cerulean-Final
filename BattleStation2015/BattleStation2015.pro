TEMPLATE = app

QT += core qml quick serialport

SOURCES += main.cpp \
    controller.cpp \
    controlpacket.cpp \
    motor.cpp \
    model.cpp \
    serial.cpp \
    mainthread.cpp \
    joystick.cpp \
    sdlwrap.cpp \
    thruster.cpp

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

win32 {

    INCLUDEPATH += $$PWD/SDL/include
    DEPENDPATH += $$PWD/SDL/include

    !contains(QMAKE_TARGET.arch, x86_64) {
        #x86 / 32-bit Windows define
        LIBS += -L$$PWD/SDL/lib/x86/ -lSDL2
    } else {
        #x86_64 / 64-bit Window define
        LIBS += -L$$PWD/SDL/lib/x64/ -lSDL2
    }
}

#linux-g++ {
#    LIBS += -L$$PWD/../SDL/lib/x64/ -lSDL2
#    INCLUDEPATH += $$PWD/SDL/include
#    DEPENDPATH += $$PWD/SDL/include
#}


macx {
    INCLUDEPATH += $$PWD/SDL/include
    INCLUDEPATH += -F/Library/Frameworks
    QMAKE_LFLAGS += -F/Library/Frameworks/ -framework SDL2
}

HEADERS += \
    controller.h \
    controlpacket.h \
    main.h \
    model.h \
    motor.h \
    serial.h \
    mainthread.h \
    joystick.h \
    sdlwrap.h \
    thruster.h
