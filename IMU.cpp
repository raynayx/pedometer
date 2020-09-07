/*
Step counter initial implementation


*/
#include "IMU.h"
#include "CurieIMU.h"


float max_threshold,min_threshold, threshold = 0.43;  // dynamic threshold
float max_reading,min_reading;      // max and min of all 3 axes
float precision = 0.1;                    // step counting precision
int sampling_counter = 0;
float sample_new = 0.0,sample_old = 0.0;    //linear shift register
float sample_result = 0.0;
int steps = 0;   // number of steps

void setupSensor(int accelRange, int accelRate)
{
    CurieIMU.begin();
    CurieIMU.setAccelerometerRange(accelRange);
    CurieIMU.setAccelerometerRate(accelRate);           //set accelerometer SAMPLING RATE
}

void calibrateAccel()
{
CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);  
}

float maxVal(float x, float y, float z)
{
     if(x > y && x > z)
        {
            return x;
        }
        else if(y > x && y > z)
        {
            return y;
        }
        else if(z > x && z > y)
        {
            return z;
        }
        // return any if all are equal
}

float minVal(float x, float y, float z)
{
     if(x < y && x < z)
        {
            return x;
        }
        else if(y < x && y < z)
        {
            return y;
        }
        else if(z < x && z < y)
        {
            return z;
        }

        // return any if all are equal
}

int countStep()
{
    float x,y,z;                          //accelerometer readings
    float x_result,y_result,z_result;     // digital filter: just an average of 4 successive readings
    float x_new = 0,y_new = 0,z_new = 0;  //current readings
    float delta;                //difference between threshold and sample_result


    // read the sensor values from all axes and find the average of every four sets
    for (int i = 0; i < 4; i++)
    {
        if(CurieIMU.dataReady(ACCEL))
        {
            CurieIMU.readAccelerometerScaled(x,y,z);
            x_new += abs(x);
            y_new += abs(y);
            z_new += abs(z); 
            delay(20); 
        }
        
        
    }
    
    x_result = x_new/4;
    y_result = y_new/4;
    z_result = z_new/4;

//    Serial.print("A \t");
    Serial.print(abs(x_result));
    Serial.print("\t");
    Serial.print(abs(y_result));
    Serial.print("\t");
    Serial.println(abs(z_result));
    Serial.print("counter\t");
    Serial.println(sampling_counter);
    Serial.print("max_reading \t");
    Serial.println(max_reading);
    Serial.print("min_reading\t");
    Serial.println(min_reading);
    Serial.print("threshold\t");
    Serial.println(threshold);
    Serial.print("Steps\t");
    Serial.println(steps);
//    Serial.println(CurieIMU.getAccelerometerRate());    DEFAULT SAMPLING RATE IS 100 Hz

    if(sampling_counter == 0)
    {

    
        // getting the maximum reading across all 3 axes
       max_reading = maxVal(x_result,y_result,z_result);

        // getting the minimum reading across all 3 axes
        min_reading = minVal(x_result,y_result,z_result);

        threshold = (max_reading + min_reading)/2;          //compute dynamic threshold
    }
    sampling_counter++;

    if(sampling_counter == 50)
    {
        sampling_counter = 0;

        // reinitiate the max and min threshold values
        // getting the maximum reading across all 3 axes
        max_reading = maxVal(x_result,y_result,z_result);

        // getting the minimum reading across all 3 axes
        min_reading = minVal(x_result,y_result,z_result);

        threshold = (max_reading + min_reading)/2;          //compute dynamic threshold
    }

    // finding the changes in acceleration and comparing it with the preset value
    // shift sample_new to sample_old immediately new data is avaialable
    // shift sample_result to sample_new if:
    //  delta in acceleration is greater than predefined precision
    // else sample_new is unchanged
    sample_result = maxVal(x_result,y_result,z_result); 

    sample_old = sample_new;
    delta = threshold - sample_result;      //change sufficient? 
    if(delta > precision)
    {
       sample_new = sample_result;
       Serial.println("delta greater than precision");
    }
    
    if(sample_new < sample_old)
    {
        steps++;
    }
    return steps;
}

