#ifndef TYPES_H_
#define TYPES_H_

#include <CircularBuffer.h>
#include <Arduino.h>




#define maxSize 50
#define THRESHOLD 0.09


struct COEFFICIENTS
{
    double alpha[3];
    double beta[3];
};
struct axes
{
    double x; 
    double y; 
    double z;
};
struct axesArr
{ 
    axes arr[50];
};

struct parsedAxesArr
{
    axes uArr[50];
    axes gArr[50];
};

struct oneDArr
{
    double oneDArr[50];
};

extern unsigned long steps;                                       //total steps
extern CircularBuffer<axes,maxSize> rawIMUData;        //raw data from IMU
// extern CircularBuffer<axes,maxSize> filteredBuff;      //filterd data buffer
extern axes rawIMUDataArray[maxSize];                      // rawIMUData moved from Circular Buffer to static array 
extern axes filteredArray_G[maxSize];                     //filtered data array(GRAVITY)
extern axes filteredArray_U[maxSize];                      //filtered data array(USER)
typedef CircularBuffer<axes,maxSize> CB;              // shorter alias to CircularBuffer

 
#endif