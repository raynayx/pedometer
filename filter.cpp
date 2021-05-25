#include "filter.h"
#define DEBUG

CB filteredBuff; 
axes filteredArray_G[maxSize];
void Filter::filter(CB &data,COEFFICIENTS &coefficients)                //make filteredArray_G a parameter
{
    Serial.print(F("3D filter()\t"));
    // filteredBuff.push({0,0,0});
    // filteredBuff.push({0,0,0});

    filteredArray_G[0]={0,0,0};
    filteredArray_G[1]={0,0,0};

    double x,y,z;       //store of temporary values

    for(int i = 2; i < maxSize;i++)
    {

        x=
        
        coefficients.alpha[0]*
        (data[i].x * coefficients.beta[0]+data[i-1].x * coefficients.beta[1]+
        data[i-2].x * coefficients.beta[2]-filteredArray_G[i-1].x * coefficients.alpha[1]-
        filteredArray_G[i-2].x * coefficients.alpha[2]
        );
        Serial.print(x);TAB;
   

        y=
        
        coefficients.alpha[0]*
        (data[i].y * coefficients.beta[0]+data[i-1].y * coefficients.beta[1]+
        data[i-2].y * coefficients.beta[2]-filteredArray_G[i-1].y * coefficients.alpha[1]-
        filteredArray_G[i-2].y * coefficients.alpha[2]
        );
        Serial.print(y);TAB;
 

        z=
        
        coefficients.alpha[0]*
        (data[i].z * coefficients.beta[0]+data[i-1].z * coefficients.beta[1]+
        data[i-2].z * coefficients.beta[2]-filteredArray_G[i-1].z * coefficients.alpha[1]-
        filteredArray_G[i-2].z * coefficients.alpha[2]
        );
        Serial.println(z);   


        filteredArray_G[i] = {x,y,z};
        #ifdef DEBUG
        Serial.print(F("filtered\t")); 
        Serial.print(filteredArray_G[i].x); TAB;
        Serial.print(filteredArray_G[i].y); TAB;
        Serial.println(filteredArray_G[i].z);
        #endif
    }
}

//1D filter TODO: cross check method
void Filter::filter(double* data, COEFFICIENTS &coefficients,double* filteredData)
{
    Serial.print(F("1D filter()\t"));
    filteredData[0] = 0.0;
    filteredData[1] = 0.0;

    for(int i = 2; i < maxSize; i++)
    {
        filteredData[i] =
        coefficients.alpha[0]*
        (data[i]*coefficients.beta[0] + data[i-1]*coefficients.beta[1] + 
        data[i-2]*coefficients.beta[2] - filteredData[i-1]*coefficients.alpha[1] - 
        filteredData[i-2]*coefficients.alpha[2]
        );
    }
}

void Filter::high_1_hz(CB &data)
{
    filter(data,HIGH_1_HZ);
}

void Filter::low_5_hz(CB &data)
{
    filter(data,LOW_5_HZ);
}


void Filter::low_0_hz(CB &data)
{
    filter(data,LOW_0_HZ);
}



// dot product filters
void Filter::high_1_hz(double* data,double* filteredData)
{
    filter(data,HIGH_1_HZ,filteredData);
}

void Filter::low_5_hz(double* data,double* filteredData)
{
    filter(data,LOW_5_HZ,filteredData);
}


void Filter::low_0_hz(double* data,double* filteredData)
{
    filter(data,LOW_0_HZ,filteredData);
}