#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDebug>

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

public:
    explicit Controller();
    ~Controller();

    bool running() const;
    void setRunning(bool running);

private:
    bool m_running;
    quint8 thrusterControl[8];

public slots:
    void doSomething();
    void thrusterControlMax(int address, int value);

private slots:

signals:
    void runningChanged();

};

#endif // CONTROLLER_H
