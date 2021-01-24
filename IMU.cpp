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
#include <Arduino.h>

LSM9DS1 lsm;
IMU imu;



axesArr IMU::xlValues()
{
  axesArr vals;
  if(lsm.accelAvailable())
  {
    for(int i = 0; i < 50; i++)
    {
      lsm.readAccel();
      vals.arr[i].x = lsm.calcAccel(lsm.ax);
      vals.arr[i].y = lsm.calcAccel(lsm.ay);
      vals.arr[i].z = lsm.calcAccel(lsm.az);
    }
  }
  else
  {
   // do something else 
  }
  return vals;
}

void IMU::setupSensor()
{
//   pinMode(intPin,INPUT_PULLUP);
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


unsigned long IMU::countStep()
{
axes reading = {0,0,0};   // result after digital filter       
axes maxSample = {0.1,0.3,0.9};        //maximum of 3 axes
axes minSample = {0.0,0.0,0.0};         // minimum of 3 axes
axes temp = {0,0,0};
axes delta;

  
 if (lsm.accelAvailable())
  {
      for(int i = 0; i < 4; i++)
      { 
      lsm.readAccel();
      reading.x += abs(lsm.calcAccel(lsm.ax));
      reading.y += abs(lsm.calcAccel(lsm.ay));
      reading.z += abs(lsm.calcAccel(lsm.az));
      interval++;
      }
      interval = interval >= 100 ? 0: interval;
       
      reading.x = reading.x/4;
      reading.y = reading.y/4;
      reading.z = reading.z/4;
  }
  else
  {
    return steps;
  }

  
stored_reading[sampling_counter] = reading;

for(int i = 0; i < 4; i++)
{
  int count = sampling_counter + i;

  if(count == 50)
  {
    temp.x += stored_reading[0].x;
    temp.y += stored_reading[0].y;
    temp.z += stored_reading[0].z;
  }
  else if(count == 51)
  {
    temp.x += stored_reading[1].x;
    temp.y += stored_reading[1].y;
    temp.z += stored_reading[1].z;
  }
  else if( count == 52)
  {
    temp.x += stored_reading[2].x;
    temp.y += stored_reading[2].y;
    temp.z += stored_reading[2].z;
  }
  else
  {
    temp.x += stored_reading[count].x;
    temp.y += stored_reading[count].y;
    temp.z += stored_reading[count].z;
  }
}

temp.x = temp.x/4;
temp.y = temp.y/4;
temp.z = temp.z/4;
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


// delta.x = threshold.x - abs(stored_reading[sampling_counter].x);
// delta.y = threshold.y - abs(stored_reading[sampling_counter].y);
// delta.z = threshold.z - abs(stored_reading[sampling_counter].z);

delta.x = threshold.x - abs(temp.x);
delta.y = threshold.y - abs(temp.y);
delta.z = threshold.z - abs(temp.z);

if(maxAxis(delta) > precision) 
{
//  Serial.println(F("**"));
  sample_old = sample_new;
  sample_new = maxAxis(temp); //sample_result
  
  if(sample_new < sample_old  - 0.1)
  {
//    Serial.print(F("new \t"));
//    Serial.println(sample_new,6);
    
    Serial.print(F("old \t"));
    Serial.println(sample_old,6);
    
    if((millis() - timeOfPreviousStep)  > 200)
    { 
        Serial.print(F("interval \t"));
      Serial.println(interval);
      if(interval >= 10 && interval <= 100)
      {
        timeOfPreviousStep = millis();
//        Serial.println(F("##"));
        steps++;
      }
      
      }
    }
  }
  return steps;
}



// from LSM9DS1 library
axes IMU::printAccel()
{
  axes a;
  Serial.print(F("A: "));

#ifdef PRINT_CALCULATED
  if ( lsm.accelAvailable() )
  {
    lsm.readAccel();
  }
  a.x = lsm.calcAccel(lsm.ax);
  a.y = lsm.calcAccel(lsm.ay);
  a.z = lsm.calcAccel(lsm.az);
  
//  Serial.print(a.x);
//  Serial.print(", ");
//  Serial.print(a.y);
//  Serial.print(", ");
//  Serial.print(a.z);
//  Serial.println(" g");

  
#elif defined PRINT_RAW
if ( lsm.accelAvailable() )
  {
    lsm.readAccel();
  }
  Serial.print(lsm.ax);
  Serial.print(", ");
  Serial.print(lsm.ay);
  Serial.print(", ");
  Serial.println(lsm.az);


#endif
  return a;
}

void IMU::myWait(int interval)
{  
  unsigned long  start = millis();
  while(millis() - start < interval);
}

axes IMU::maxVal(axes arr[50])
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
axes IMU::minVal(axes arr[50])
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

float IMU::maxAxis (axes a)
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

//void IMU::configureLSM9DS1Interrupts()
//{
//   imu.configAccelInt(XHIE_XL|YHIE_XL|ZHIE_XL, false);
//  // 4. Configure accelerometer threshold:
//  //   - 20: Threshold (raw value from accel)
//  //     Multiply this value by 128 to get threshold value.
//  //     (20 = 2600 raw accel value)
//  //   - X_AXIS: Write to X-axis threshold
//  //   - 10: duration (based on ODR)
//  //   - false: wait (wait [duration] before interrupt goes low)
//  imu.configAccelThs(20, X_AXIS, 10, false);
//  imu.configAccelThs(25, Y_AXIS, 10, false);
//  imu.configAccelThs(200, Z_AXIS, 10, false);
//  // 5. Configure INT1 - assign it to gyro interrupt
//  //   - XG_INT1: Says we're configuring INT1
//  //   - INT1_IG_G | INT1_IG_XL: Sets interrupt source to 
//  //     both gyro interrupt and accel
//  //   - INT_ACTIVE_LOW: Sets interrupt to active low.
//  //         (Can otherwise be set to INT_ACTIVE_HIGH.)
//  //   - INT_PUSH_PULL: Sets interrupt to a push-pull.
//  //         (Can otherwise be set to INT_OPEN_DRAIN.)
//  imu.configInt(XG_INT1, INT1_IG_G | INT_IG_XL, INT_ACTIVE_LOW, INT_PUSH_PULL);
//
//  ////////////////////////////////////////////////
//  // Configure INT2 - Gyro and Accel Data Ready //
//  ////////////////////////////////////////////////
//  // Configure interrupt 2 to fire whenever new accelerometer
//  // or gyroscope data is available.
//  // Note XG_INT2 means configuring interrupt 2.
//  // INT_DRDY_XL is OR'd with INT_DRDY_G
//  imu.configInt(XG_INT2, INT_DRDY_XL | INT_DRDY_G, INT_ACTIVE_LOW, INT_PUSH_PULL);
//  
//}

//void IMU::ack()
//{
//  imu.getAccelIntSrc();
//}


//void IMU::checkInt()
//{
// // INT1 fires when our gyro or accelerometer thresholds
//  // are exceeded.
//  // It's configured to be active LOW:
//  if (digitalRead(intPin) == LOW)
//  {
//    // Let's keep track of how long the interrupt is active.
//    // We turned off latching, so this pin will stay low
//    // as long as the threshold is exceeded:
//    unsigned long durationStart = millis();
//
//    // Call getGyroIntSrc() and getAccelIntSrc() to determine
//    // if the gyro or accel generated the input (and why).
//    Serial.println("\tINT1 Active!");
//    Serial.print("\t\tGyro int: 0x");
//    Serial.println(imu.getGyroIntSrc(), HEX);
//    Serial.print("\t\tAccel int: 0x");
//    Serial.println(imu.getAccelIntSrc(), HEX);
//
//    // While the interrupt remains active, loop:
//    while (digitalRead(intPin) == LOW)
//    {
//      //imu.getGyroIntSrc();
//      //imu.getAccelIntSrc();
//      
//    }
//    Serial.print("\tINT1 Duration: ");
//    Serial.println(millis() - durationStart);
////    return true;
//  }
//  else
//  {
//    return;
//  }
//}
