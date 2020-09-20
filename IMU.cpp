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
static unsigned long lastPrint = 0; // Keep track of print time

#define DECLINATION -8.58

void printGyro();
void printAccel();
void printMag();
void printAttitude(float ax, float ay, float az, float mx, float my, float mz);

LSM9DS1 imu;

float max_threshold,min_threshold, threshold = 0.23;  // dynamic threshold
float thresholds[3];                //threshold for all 3 axes x,y,z in that order
float max_reading[3],min_reading[3];      // max and min of all 3 axes
float x_store[50],y_store[50],z_store[50];

float precision = 0.2;                    // step counting precision
int sampling_counter = 0;
float sample_new = 0,sample_old =0;    //linear shift register
float sample_result[3];
int steps = 0;   // number of steps

void setupSensor(int accelRange, int accelRate)
{
//    CurieIMU.begin();
//    CurieIMU.setAccelerometerRange(accelRange);
//    CurieIMU.setAccelerometerRate(accelRate);           //set accelerometer SAMPLING RATE


}

void calibrateAccel()
{
// calibrate sensor  
}

float maxVal(float x[50])
{
float max = x[0];
 for (int i = 0; i < 50; i++)
 {
    if(x[i] > max)
    {
        max = x[i];
    }
 }
 return max;
}

float maxVal2(float x[3])
{
float max = x[0];
 for (int i = 0; i < 3; i++)
 {
    if(x[i] > max)
    {
        max = x[i];
    }
 }
 return max;
}

float minVal(float x[50])
{
float min = x[0];
 for (int i = 0; i < 50; i++)
 {
    if(x[i] < min)
    {
        min = x[i];
    }
 }
 return min;
}

int countStep()
{
    float readings[3];                          //accelerometer readings
    float results[3];     // digital filter: just an average of 4 successive readings
    float new_readings[3] = {0.0,0.0,0.0};  //current readings
    float delta[3];                //difference between threshold and sample_result


    // read the sensor values from all axes and find the average of every four sets
    for (int i = 0; i < 4; i++)
    {
        if(1) //check for accel data availability from sensor
        {
//            CurieIMU.readAccelerometerScaled(readings[0],readings[1],readings[2]);      Read x,y,z from accel sensor
            for(int i = 0; i < 3;i++)
            {
                new_readings[i] += abs(readings[i]);
            } 
            delay(20); 
        }
        
        
    }
    
    for(int i = 0; i < 3; i++)
    {
        results[i] = new_readings[i]/4;
    }

   
    x_store[sampling_counter] = results[0];
    y_store[sampling_counter] = results[1];
    z_store[sampling_counter] = results[2];

    
//    Serial.print("A \t");
    for(int i = 0; i < 3; i++)
    {
        Serial.print(abs(results[i]));
        Serial.print("\t");
    }
    Serial.print("counter\t");
    Serial.println(sampling_counter);

    for(int i = 0; i < 3;i++)
    {
        Serial.print("max_reading \t");
        Serial.println(max_reading[i]);
        Serial.print("min_reading\t");
        Serial.println(min_reading[i]);
    }
    
    for(int i = 0; i <3; i++)
    {
        Serial.print("threshold\t");
        Serial.println(thresholds[i]);
    }
   
    Serial.print("Steps\t");
    Serial.println(steps);

    Serial.print("sample_new\t");
    Serial.println(sample_new);

    Serial.print("sample_old\t");
    Serial.println(sample_old);

    Serial.print("delta\t");
    Serial.println(maxVal2(delta));

    Serial.print("precision\t");
    Serial.println(precision);

//    Serial.println(CurieIMU.getAccelerometerRate());    DEFAULT SAMPLING RATE IS 100 Hz

    if(sampling_counter == 0)
    {
        // getting the maximum reading across all 3 axes
        max_reading[0] = maxVal(x_store);
        max_reading[1] = maxVal(y_store);
        max_reading[2] = maxVal(z_store);

        // getting the minimum reading across all 3 axes
        min_reading[0] = minVal(x_store);
        min_reading[1] = minVal(y_store);
        min_reading[2] = minVal(z_store);

        thresholds[0] = (max_reading[0] + min_reading[0])/2;          //compute dynamic threshold
        thresholds[1] = (max_reading[1] + min_reading[1])/2;
        thresholds[2] = (max_reading[2] + min_reading[2])/2;
    }
    sampling_counter++;

    if(sampling_counter == 50)
    {
        sampling_counter = 0;

        // reinitiate the max and min threshold values
        // getting the maximum reading across all 3 axes
       // getting the maximum reading across all 3 axes
        max_reading[0] = maxVal(x_store);
        max_reading[1] = maxVal(y_store);
        max_reading[2] = maxVal(z_store);

        // getting the minimum reading across all 3 axes
        min_reading[0] = minVal(x_store);
        min_reading[1] = minVal(y_store);
        min_reading[2] = minVal(z_store);

        thresholds[0] = (max_reading[0] + min_reading[0])/2;          //compute dynamic threshold
        thresholds[1] = (max_reading[1] + min_reading[1])/2;
        thresholds[2] = (max_reading[2] + min_reading[2])/2;
    }

    // finding the changes in acceleration and comparing it with the preset value
    // shift sample_new to sample_old immediately new data is avaialable
    // shift sample_result to sample_new if:
    //  delta in acceleration is greater than predefined precision
    // else sample_new is unchanged

    
    for(int i = 0; i < 3; i++)
    {
        sample_result[i] = max_reading[i];
        delta[i] = thresholds[i] - sample_result[i];
        
    }
    

    if(abs(maxVal2(delta)) > precision)
    {
        sample_new = maxVal2(sample_result);
        Serial.println("delta greater than precision");
        if(sample_new < sample_old)
        {
            steps++;
        }
 
    }
    
    sample_old = sample_new;
    

    
    return steps;
}






// from LSM9DS1 library
void printGyro()
{
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.
  Serial.print("G: ");
  
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcGyro helper function to convert a raw ADC value to
  // DPS. Give the function the value that you want to convert.
  Serial.print(imu.calcGyro(imu.gx), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz), 2);
  Serial.println(" deg/s");

   // print to OLED screen 
//  oled.print(imu.calcGyro(imu.gx), 2);
//  oled.print(", ");
//  oled.print(imu.calcGyro(imu.gy), 2);
//  oled.print(", ");
//  oled.print(imu.calcGyro(imu.gz), 2);
//  oled.println(" deg/s");
#elif defined PRINT_RAW
  Serial.print(imu.gx);
  Serial.print(", ");
  Serial.print(imu.gy);
  Serial.print(", ");
  Serial.println(imu.gz);


// oled.print(imu.gx);
//  oled.println(", ");
//  oled.print(imu.gy);
//  oled.println(", ");
//  oled.println(imu.gz);
#endif
}


void printAccel()
{
  // Now we can use the ax, ay, and az variables as we please.
  // Either print them as raw ADC values, or calculated in g's.
  Serial.print("A: ");
//  oled.println("A: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcAccel helper function to convert a raw ADC value to
  // g's. Give the function the value that you want to convert.
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println(" g");


//  oled.println(imu.calcAccel(imu.ax), 2);
//  oled.println(imu.calcAccel(imu.ay), 2);
//  oled.print(imu.calcAccel(imu.az), 2);
//  oled.println(" g");
//  oled.println();
//  oled.println();
//  oled.println();
//  oled.println();

  
#elif defined PRINT_RAW
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay);
  Serial.print(", ");
  Serial.println(imu.az);

  oled.print(imu.ax);
  oled.println(", ");
  oled.print(imu.ay);
  oled.println(", ");
  oled.println(imu.az);
#endif

}

void printMag()
{
  // Now we can use the mx, my, and mz variables as we please.
  // Either print them as raw ADC values, or calculated in Gauss.
  Serial.print("M: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcMag helper function to convert a raw ADC value to
  // Gauss. Give the function the value that you want to convert.
  Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");
#elif defined PRINT_RAW
  Serial.print(imu.mx);
  Serial.print(", ");
  Serial.print(imu.my);
  Serial.print(", ");
  Serial.println(imu.mz);
#endif
}



void printAttitude(float ax, float ay, float az, float mx, float my, float mz)
{
    float roll = atan2(ay, az);
    float pitch = atan2(-ax, sqrt(ay * ay + az * az));

    float heading;
  if (my == 0)
    heading = (mx < 0) ? PI : 0;
  else
    heading = atan2(mx, my);

  heading -= DECLINATION * PI / 180;

  if (heading > PI) heading -= (2 * PI);
  else if (heading < -PI) heading += (2 * PI);

  // Convert everything from radians to degrees:
  heading *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;

  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Heading: "); Serial.println(heading, 2);
}
