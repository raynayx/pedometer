#include "parser.h"
#include "filter.h"
// #define DEBUG


axes filteredArray_U[maxSize]; 


void Parser::parse()
{
    Filter fp;

    //get acceleration in the direction of gravity by calling Filter.low_0_hz
    fp.low_0_hz(rawIMUData);
    //filteredArray_G now has the filtered acceleration data which is in the direction of gravity
    for(int i =0; i < maxSize; i++)
    {
        //get user acceleration by subtracting gravity from total
        filteredArray_U[i].x = rawIMUDataArray[i].x - filteredArray_G[i].x;
        filteredArray_U[i].y = rawIMUDataArray[i].y - filteredArray_G[i].y;
        filteredArray_U[i].z = rawIMUDataArray[i].z - filteredArray_G[i].z;

        #ifdef DEBUG
        Serial.print("filtered User\t"); 
        Serial.print(filteredArray_U[i].x); Serial.print("\t");
        Serial.print(filteredArray_U[i].y); Serial.print("\t");
        Serial.print(filteredArray_U[i].z); Serial.println();
        #endif
    }
}