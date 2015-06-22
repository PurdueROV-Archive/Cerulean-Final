#include "thruster.h"

void Thruster::normalize(int values[], int size) {
    int valuesMax = 0;
    int max = 1000;

    //get Max value
    for (int i = 0; i < size; i++) {
        if (abs(values[i]) > max) {
            valuesMax = abs(values[i]);
        }
    }

    if (valuesMax > max) {
        //Normalize the values based off max
        float n = ((float) max) / ((float) valuesMax);
        for (int i = 0; i < size; i++) {
            values[i] = (int) (n * values[i]);
        }
    }
}

quint8 Thruster::convert(int val) {
    quint8 ret = 0;
    bool negative = (val < 0) ? true : false;
    ret = (quint8) abs(val * .128);

    if (negative){
        ret |= 0x80; // 0b10000000
    }
    return ret;
}
