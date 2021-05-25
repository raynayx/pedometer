#include "modelIMU.h"


CB rawIMUData;        //raw data from IMU
axes rawIMUDataArray[maxSize];                  // static array to store every maxSize set of IMU data


void IMU::setupSensor()
{
   Wire.begin();

  if (!lsm.begin() ) // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  {
    Serial.println(F("Failed to communicate with LSM9DS1."));
    Serial.println(F("Double-check wiring."));
    while (1);
  }
//  Wire.setClock(400000);
  lsm.settings.gyro.enabled = false;
  lsm.settings.mag.enabled = false;
  
  lsm.settings.accel.scale = 2;
  // SAMPLE RATE SETTINGS
  // 1 = 10 Hz    4 = 238 Hz
  // 2 = 50 Hz    5 = 476 Hz
  // 3 = 119 Hz   6 = 952 Hz
  lsm.settings.accel.sampleRate = 2;

  
  lsm.begin();

}



void IMU::fillCircularBuffer()
{
    #define X lsm.calcAccel(lsm.ax)
    #define Y lsm.calcAccel(lsm.ay)
    #define Z lsm.calcAccel(lsm.az)

    #define TAB Serial.print(F("\t"))


    Serial.println(F("Fill buffer"));

   if(lsm.accelAvailable())
    {
        if(rawIMUData.isEmpty())
        {
            for(int i=0; i < maxSize; i++)
            {
                lsm.readAccel();
                rawIMUData.push({X,Y,Z});

            }
        }
        lsm.readAccel();
        rawIMUData.push({X,Y,Z});
    }
    else
    {
      Serial.println(F("Accel not available\t"));
    }



    // // move current data set into static array 
    for(int i=0; i < maxSize; i++)
    {
      rawIMUDataArray[i].x = rawIMUData[i].x;
      rawIMUDataArray[i].y = rawIMUData[i].y;
      rawIMUDataArray[i].z = rawIMUData[i].z;
    }

    for(int i=0; i < maxSize; i++)
    {
      Serial.print(F("rawDataArr"));TAB;
      Serial.print(rawIMUDataArray[i].x);TAB;
      Serial.print(rawIMUDataArray[i].y);TAB;
      Serial.println(rawIMUDataArray[i].z);

    }
}