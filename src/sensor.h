#ifndef SENSOR_H
#define SENSOR_H

class Sensor{
public:
    Sensor(int pin_S0, int pin_S1, int pin_S2, int pin_S3, int pin_OUT);
    void reading();
};

#endif