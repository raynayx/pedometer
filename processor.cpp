#include "processor.h"
#include "filter.h"
// #define DEBUG



void Processor::dotProduct(double* result)
{
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
}



//rewritten dotProduct filter  returns the filtered result
void Processor::filter(double* dp, double* filteredD)
{
    Filter fp;

    //take out low freq
    double filteredD_L[maxSize];
    fp.low_0_hz(dp,filteredD_L);

    #ifdef DEBUG
      for(int i = 0; i < maxSize; i++)
      {
          Serial.print("filtered 1D(LOW_0)\t");
          Serial.println(filteredD_L[i]);
      }
    #endif

    //take out high freq
    fp.high_1_hz(filteredD_L,filteredD);

    #ifdef DEBUG
      for(int i=0; i < maxSize; i++)
      {
        Serial.print("filtered 1D(HIGH_1)\t");
        Serial.println(filteredD[i]);
      }
    #endif

}