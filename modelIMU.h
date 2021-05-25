// #pragma once

#include "types.h"
#include <Wire.h>
#include <SparkFunLSM9DS1.h>


class IMU
{
    public:

    //LSM9DS1 IMU declaration
    LSM9DS1 lsm;
    //setup the range and other parameters of the sensor
    void setupSensor();

    //push data into CircularBuffer
    void fillCircularBuffer();

    private:

};