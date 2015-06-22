#ifndef THRUSTER_H
#define THRUSTER_H

#include "main.h"

class Thruster
{
public:
    Thruster(){};
    ~Thruster(){};

    static void normalize(int values[], int size);
    static quint8 convert(int val);
};

#endif // THRUSTER_H
