#include "processor.h"
#include "filter.h"
#define DEBUG

double* Processor::dotProduct()
{
    double result[maxSize];
    for(int i=0; i < maxSize; i++)
    {
      result[i] =
      filteredArray_G[i].x * filteredArray_U[i].x +
      filteredArray_G[i].y * filteredArray_U[i].y +
      filteredArray_G[i].z * filteredArray_U[i].z;

      #ifdef DEBUG
        Serial.print("dot product \t");
        Serial.println(result[i]);
      #endif

      
    }
    return result;
}

double* Processor::filter()
{
    Filter fp;
    double* dp = dotProduct();

    //take out low freq
    double* filteredD = fp.low_0_hz(dp);

    #ifdef DEBUG
      for(int i = 0; i < maxSize; i++)
      {
          Serial.print("filtered 1D(LOW_0)\t");
          Serial.println(filteredD[i]);
      }
    #endif

    //take out high freq
    filteredD = fp.high_1_hz(filteredD);

    #ifdef DEBUG
      for(int i=0; i < maxSize; i++)
      {
        Serial.print("filtered 1D(HIGH_1)\t");
        Serial.println(filteredD[i]);
      }
    #endif

    return filteredD;

}
