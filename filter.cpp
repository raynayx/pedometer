
/*

*/
#include "filter.h"



axesArr Filter::low_0_hz(axesArr data)
{
    filter(data,LOW_0_HZ);
}
//low_5_hz(data)
axesArr Filter::low_5_hz(axesArr data)
{
    filter(data,LOW_5_HZ);
}
//high_1_hz(data)
axesArr Filter::high_1_hz(axesArr data)
{
    filter(data,HIGH_1_HZ);
}

oneDArr Filter::low_0_hz(oneDArr data)
{
    filter(data,LOW_0_HZ);
}
//low_5_hz(data)
oneDArr Filter::low_5_hz(oneDArr data)
{
    filter(data,LOW_5_HZ);
}
//high_1_hz(data)
oneDArr Filter::high_1_hz(oneDArr data)
{
    filter(data,HIGH_1_HZ);
}

axesArr Filter::filter(axesArr data,COEFFICIENTS coefficients)
{
    axesArr filtered_data;
    filtered_data.arr[0]={0.0,0.0,0.0};
    filtered_data.arr[1]={0.0,0.0,0.0};

//    data.arr[1].x;

    for(int i = 2; i < 50; i++)
    {
        filtered_data.arr[i].x=
        coefficients.alpha[0] *
            (data.arr[i].x*coefficients.beta[0] + data.arr[i-1].x*coefficients.beta[1]+
            data.arr[i-2].x*coefficients.beta[2] - filtered_data.arr[i-1].x*coefficients.alpha[1]-
            filtered_data.arr[i-2].x*coefficients.alpha[2]  
            );

        filtered_data.arr[i].y=
        coefficients.alpha[0] *
            (data.arr[i].y*coefficients.beta[0] + data.arr[i-1].y*coefficients.beta[1]+
            data.arr[i-2].y*coefficients.beta[2] - filtered_data.arr[i-1].y*coefficients.alpha[1]-
            filtered_data.arr[i-2].y*coefficients.alpha[2]  
            );

        filtered_data.arr[i].z=
        coefficients.alpha[0] *
            (data.arr[i].z*coefficients.beta[0] + data.arr[i-1].z*coefficients.beta[1]+
            data.arr[i-2].z*coefficients.beta[2] - filtered_data.arr[i-1].z*coefficients.alpha[1]-
            filtered_data.arr[i-2].z*coefficients.alpha[2]  
            );

    }

    return filtered_data;
}    
oneDArr Filter::filter(oneDArr data,COEFFICIENTS coefficients)
{
    oneDArr filtered_data;
    filtered_data.oneDArr[0]=0.0;
    filtered_data.oneDArr[1]=0.0;


    for(int i = 2; i < 50; i++)
    {
        filtered_data.oneDArr[i]=
        coefficients.alpha[0] *
            (data.oneDArr[i]*coefficients.beta[0] + data.oneDArr[i-1]*coefficients.beta[1]+
            data.oneDArr[i-2]*coefficients.beta[2] - filtered_data.oneDArr[i-1]*coefficients.alpha[1]-
            filtered_data.oneDArr[i-2]*coefficients.alpha[2]  
            );
    }

    return filtered_data;
}
