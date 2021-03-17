#include "filter.h"
// #define DEBUG

CB filteredBuff; 
axes filteredArray_G[maxSize];
void Filter::filter(CB &data,COEFFICIENTS &coefficients)
{
    // filteredBuff.push({0,0,0});
    // filteredBuff.push({0,0,0});

    filteredArray_G[0]={0,0,0};
    filteredArray_G[1]={0,0,0};

    double x,y,z;       //store of temporary values

    for(int i = 2; i < maxSize;i++)
    {
        // x=
        
        // coefficients.alpha[0]*
        // (data[i].x * coefficients.beta[0]+data[i-1].x * coefficients.beta[1]+
        // data[i-2].x * coefficients.beta[2]-filteredBuff[i-1].x * coefficients.alpha[1]-
        // filteredBuff[i-2].x * coefficients.alpha[2]
        // );

        x=
        
        coefficients.alpha[0]*
        (data[i].x * coefficients.beta[0]+data[i-1].x * coefficients.beta[1]+
        data[i-2].x * coefficients.beta[2]-filteredArray_G[i-1].x * coefficients.alpha[1]-
        filteredArray_G[i-2].x * coefficients.alpha[2]
        );
        Serial.println(x);


        // y=
        // coefficients.alpha[0]*
        // (data[i].y * coefficients.beta[0]+data[i-1].y * coefficients.beta[1]+
        // data[i-2].y * coefficients.beta[2]-filteredBuff[i-1].y * coefficients.alpha[1]-
        // filteredBuff[i-2].y * coefficients.alpha[2]
        // );

        //  Serial.println(y);   

        y=
        
        coefficients.alpha[0]*
        (data[i].y * coefficients.beta[0]+data[i-1].y * coefficients.beta[1]+
        data[i-2].y * coefficients.beta[2]-filteredArray_G[i-1].y * coefficients.alpha[1]-
        filteredArray_G[i-2].y * coefficients.alpha[2]
        );
        Serial.println(y);

        // z=
        // coefficients.alpha[0]*
        // (data[i].z * coefficients.beta[0]+data[i-1].z * coefficients.beta[1]+
        // data[i-2].z * coefficients.beta[2]-filteredBuff[i-1].z * coefficients.alpha[1]-
        // filteredBuff[i-2].z * coefficients.alpha[2]
        // );

        //  Serial.println(z); 

        z=
        
        coefficients.alpha[0]*
        (data[i].z * coefficients.beta[0]+data[i-1].z * coefficients.beta[1]+
        data[i-2].z * coefficients.beta[2]-filteredArray_G[i-1].z * coefficients.alpha[1]-
        filteredArray_G[i-2].z * coefficients.alpha[2]
        );
        Serial.println(z);   

        // filteredBuff.push({x,y,z});

        filteredArray_G[i] = {x,y,z};
        #ifdef DEBUG
        Serial.print("filtered\t"); 
        Serial.print(filteredArray_G[i].x); Serial.print("\t");
        Serial.print(filteredArray_G[i].y); Serial.print("\t");
        Serial.print(filteredArray_G[i].z); Serial.println();
        #endif
    }
}


double* Filter::filter(double* data, COEFFICIENTS &coefficients)
{
    double filterdData[maxSize];

    filterdData[0] = 0.0;
    filterdData[1] = 0.0;

    for(int i = 2; i < maxSize; i++)
    {
        filterdData[i] =
        coefficients.alpha[0]*
        (data[i]*coefficients.beta[0] + data[i-1]*coefficients.beta[1] + 
        data[i-2]*coefficients.beta[2] - filterdData[i-1]*coefficients.alpha[1] - 
        filterdData[i-2]*coefficients.alpha[2]
        );
        return filterdData;
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
double* Filter::high_1_hz(double* data)
{
    filter(data,HIGH_1_HZ);
}

double*  Filter::low_5_hz(double* data)
{
    filter(data,LOW_5_HZ);
}


double*  Filter::low_0_hz(double* data)
{
    filter(data,LOW_0_HZ);
}