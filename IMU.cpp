/*
Step counter initial implementation

###########################LSM9DS1 IMU CONNECTION OVER I2C ##########################################

   LSM9DS1 --------- Arduino
   SCL ---------- SCL (A5 on older 'Duinos')
   SDA ---------- SDA (A4 on older 'Duinos')
   VDD ------------- 3.3V
   GND ------------- GND

####################################################################################################
*/

#include "IMU.h"
#include <Wire.h>
#include <SparkFunLSM9DS1.h> 

// IMU settings
#define PRINT_CALCULATED
#define PRINT_SPEED 250 // 250 ms between prints
//static unsigned long lastPrint = 0; // Keep track of print time



axes printAccel();
LSM9DS1 imu;

// #################### Steps variables###########
long steps = 0;   // number of steps
axes stored_reading[50];
int sampling_counter = 0; 
float precision = 0.1;
axes threshold = {0.1,0.1,0.1};
//####################################



void setupSensor()
{
   Wire.begin();

  if (!imu.begin() ) // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    while (1);
  }
  imu.settings.gyro.enabled = false;
  imu.settings.mag.enabled = false;
  
  imu.settings.accel.scale = 2;
  // SAMPLE RATE SETTINGS
  // 1 = 10 Hz    4 = 238 Hz
  // 2 = 50 Hz    5 = 476 Hz
  // 3 = 119 Hz   6 = 952 Hz
  imu.settings.accel.sampleRate = 2;

  
  imu.begin();
}


long countStep()
{
axes reading = {0,0,0};   // result after digital filter       
axes maxSample;        //maximum of 3 axes
axes minSample;         // minimum of 3 axes

axes delta;
float sample_new;
float sample_old;
axes sample_result;
  
 if (imu.accelAvailable())
  { 
    for (int i = 0; i < 4; i++)
    {
      imu.readAccel();
      reading.x += abs(imu.calcAccel(imu.ax));
      reading.y += abs(imu.calcAccel(imu.ay));
      reading.z += abs(imu.calcAccel(imu.az));
      myWait(20);
    }
  }

reading.x = reading.x/4;
reading.y = reading.y/4;
reading.z = reading.z/4;
  
stored_reading[sampling_counter] = reading;
sampling_counter++;


 if(sampling_counter == 50)
 {
   sampling_counter = 0;
   axes maxSample = maxVal(stored_reading);
   axes minSample = minVal(stored_reading);


   // reinitiate max and min
   //set Dynamic precision when sampling_counter == 0

   //finding dynamic threhold
  threshold.x = (maxSample.x + minSample.x)/2;
  threshold.y = (maxSample.y + minSample.y)/2;
  threshold.z = (maxSample.z + minSample.z)/2;
 }
  
 //finding the changes in acceleration and comparing it with the preset value
 //shift sample_new to sample_old immediately new data is availble
 //shift sample_result to sample_new if:
 // delta in acceleration is greater than predefined precision
 // else sample_new is unchanged

sample_result = maxSample;

delta.x = threshold.x - sample_result.x;
delta.y = threshold.y - sample_result.y;
delta.z = threshold.z - sample_result.z;

//find greatest delta
float maxDelta = maxAxis(delta);
sample_old = sample_new;

if(maxDelta > precision) 
{
  sample_new = maxAxis(sample_result);

  if(sample_new < sample_old)
  {
    steps++;
  }
}


return steps;


}


// from LSM9DS1 library


axes printAccel()
{
  axes a;
  Serial.print("A: ");

#ifdef PRINT_CALCULATED
  if ( imu.accelAvailable() )
  {
    imu.readAccel();
  }
  a.x = imu.calcAccel(imu.ax);
  a.y = imu.calcAccel(imu.ay);
  a.z = imu.calcAccel(imu.az);
  
  Serial.print(a.x);
  Serial.print(", ");
  Serial.print(a.y);
  Serial.print(", ");
  Serial.print(a.z);
  Serial.println(" g");

  
#elif defined PRINT_RAW
if ( imu.accelAvailable() )
  {
    imu.readAccel();
  }
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay);
  Serial.print(", ");
  Serial.println(imu.az);


#endif
  return a;
}

void myWait(int interval)
{  
  unsigned long  start = millis();
  while(millis() - start < interval);
}

axes maxVal(axes arr[50])
{
      float X = arr[0].x;
      float Y = arr[0].y;
      float Z = arr[0].z;

      for (int i = 0; i < 50; i++)
      {
            if(arr[i].x > X)
            {
            X = arr[i].x;
            }

            if(arr[i].y > Y )
            {
            Y = arr[i].y;
            }

            if(arr[i].z > Z)
            {
            Z = arr[i].z;
            }
      }
      return {X,Y,Z};
}
axes minVal(axes arr[50])
{
      float X = arr[0].x;
      float Y = arr[0].y;
      float Z = arr[0].z;

      for (int i = 0; i < 50; i++)
      {
            if(arr[i].x < X)
            {
            X = arr[i].x;
            }

            if(arr[i].y < Y )
            {
            Y = arr[i].y;
            }

            if(arr[i].z < Z)
            {
            Z = arr[i].z;
            }
      }
      return {X,Y,Z};
}

float maxAxis (axes a)
{
  float maxVal = abs(a.x);
  if (abs(a.y) > maxVal)
  {
    maxVal = abs(a.y);
  }
  else if( abs(a.z) > maxVal)
  {
    maxVal = abs(a.z);
  }
  return maxVal;
}
