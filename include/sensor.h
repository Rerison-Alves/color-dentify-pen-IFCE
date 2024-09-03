#ifndef SENSOR_H
#define SENSOR_H

#include "colors.h"

class Sensor{
public:
    Sensor(int pin_S0, int pin_S1, int pin_S2, int pin_S3, int pin_OUT);
    Color reading();

private:
    int redColor, greenColor, blueColor;
    int redFrequency, greenFrequency, blueFrequency;
    int S0, S1, S2, S3, OUT;
};

#endif