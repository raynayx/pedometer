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
unsigned long steps = 0;   // number of steps
axes stored_reading[50] = {0};
int sampling_counter = 0; 
float precision = 0.7;
axes threshold = {0.6,0.6,0.6};
float sample_new = 0;
float sample_old = 0;
unsigned long timeOfPreviousStep = 0;
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


unsigned long countStep()
{
axes reading = {0,0,0};   // result after digital filter       
axes maxSample = {0.1,0.3,0.9};        //maximum of 3 axes
axes minSample = {0.0,0.0,0.2};         // minimum of 3 axes

axes delta;

  
 if (imu.accelAvailable())
  { 
      imu.readAccel();
      reading.x = abs(imu.calcAccel(imu.ax));
      reading.y = abs(imu.calcAccel(imu.ay));
      reading.z = abs(imu.calcAccel(imu.az));
  }
  else
  {
    return steps;
  }

// reading.x = reading.x/4;
// reading.y = reading.y/4;
// reading.z = reading.z/4;
  
stored_reading[sampling_counter] = reading;


  axes temp = {0,0,0};
  int count = 0; 
  while(count < 4)
  {
    if(sampling_counter + count >= 50)
    {
      temp.x += stored_reading[count].x;
      temp.y += stored_reading[count].y;
      temp.z += stored_reading[count].z;
    }
    else
    {
      temp.x += stored_reading[sampling_counter + count].x;
      temp.y += stored_reading[sampling_counter + count].y;
      temp.z += stored_reading[sampling_counter + count].z; 
    }
    
    count++;
  }
  temp.x = temp.x/4;
  temp.y = temp.y/4;
  temp.z = temp.z/4;
  
  stored_reading[sampling_counter] = temp;




sampling_counter++;

 if(sampling_counter == 50)
 {
   sampling_counter = 0;
   maxSample = maxVal(stored_reading);
   minSample = minVal(stored_reading);
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


delta.x = threshold.x - abs(stored_reading[sampling_counter].x);
delta.y = threshold.y - abs(stored_reading[sampling_counter].y);
delta.z = threshold.z - abs(stored_reading[sampling_counter].z);

//find greatest delta
sample_old = sample_new;
Serial.println(maxAxis(delta));

if(maxAxis(delta) > precision) 
{
  Serial.println("**");
  sample_new = maxAxis(stored_reading[sampling_counter]); //sample_result
  
  if(sample_new < sample_old - 0.1)
  {
    Serial.print("new \t");
    Serial.println(sample_new,6);
    
    Serial.print("old \t");
    Serial.println(sample_old,6);
    
    if(millis() - timeOfPreviousStep  > 200)
    {
      timeOfPreviousStep = millis();
      Serial.println("##");
      steps++;
    }
  }
}
else if (maxAxis(delta) < precision)
{
  
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
  
//  Serial.print(a.x);
//  Serial.print(", ");
//  Serial.print(a.y);
//  Serial.print(", ");
//  Serial.print(a.z);
//  Serial.println(" g");

  
#elif defined PRINT_RAW
if ( imu.accelAvailable() )
  {
    imu.readAccel();
  }
//  Serial.print(imu.ax);
//  Serial.print(", ");
//  Serial.print(imu.ay);
//  Serial.print(", ");
//  Serial.println(imu.az);


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
      float X = abs(arr[0].x);
      float Y = abs(arr[0].y);
      float Z = abs(arr[0].z);

      for (int i = 0; i < 50; i++)
      {
            if(abs(arr[i].x) > X)
            {
            X = abs(arr[i].x);
            }

            if(abs(arr[i].y) > Y )
            {
            Y = abs(arr[i].y);
            }

            if(abs(arr[i].z) > Z)
            {
            Z = abs(arr[i].z);
            }
      }
      return {X,Y,Z};
}
axes minVal(axes arr[50])
{
      float X = abs(arr[0].x);
      float Y = abs(arr[0].y);
      float Z = abs(arr[0].z);

      for (int i = 0; i < 50; i++)
      {
            if(abs(arr[i].x) < X)
            {
            X = abs(arr[i].x);
            }

            if(abs(arr[i].y) < Y )
            {
            Y = abs(arr[i].y);
            }

            if(abs(arr[i].z) < Z)
            {
            Z = abs(arr[i].z);
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
