#include "modelIMU.h"


CB rawIMUData;        //raw data from IMU
axes rawIMUDataArray[maxSize];                  // static array to store every maxSize set of IMU data
void IMU::setupSensor()
{
   Serial.println("model IMU setup complete");
}



void IMU::fillCircularBuffer()
{

    Serial.println("Fill buffer");
    // #define X lsm.calcAccel(lsm.ax)
    // #define Y lsm.calcAccel(lsm.ay)
    // #define Z lsm.calcAccel(lsm.az)

    // if(lsm.accelAvailable())
    // {
    //     if(rawIMUData.isEmpty())
    //     {
    //         for(int i=0; i < maxSize; i++)
    //         {
    //             lsm.readAccel();
    //             rawIMUData.push({X,Y,Z});
    //         }
    //     }
    //     lsm.readAccel();
    //     rawIMUData.push({X,Y,Z});
    // }

    // // move current data set into static array 
    // for(int i=0; i < maxSize; i++)
    // {
    //   rawIMUDataArray[i].x = rawIMUData[i].x;
    //   rawIMUDataArray[i].y = rawIMUData[i].y;
    //   rawIMUDataArray[i].z = rawIMUData[i].z;
    // }
}