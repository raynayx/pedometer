#pragma once

#include "types.h"

class Filter
{
    public:
        COEFFICIENTS LOW_0_HZ ={{1.0,-1.97,0.97},{0.0000086,0.00017,0.0000863}};
        COEFFICIENTS LOW_5_HZ = {{1.0,-1.8089,0.82722},{0.095465,-0.17269,0.09563}};
        COEFFICIENTS HIGH_1_HZ = {{1.0,-1.9053,0.91},{0.953,-1.9075,0.9539}};

    
        //low_0_hz(data) 
        //split total xl into u_xl and g_xl
        axesArr low_0_hz(axesArr &data);
        //low_5_hz(data)
        axesArr low_5_hz(axesArr &data);
        //high_1_hz(data)
        axesArr high_1_hz(axesArr &data);

         //low_0_hz(data) 
        //filter low frequencies from one D 
        oneDArr low_0_hz(oneDArr &data);
        //low_5_hz(data)
        oneDArr low_5_hz(oneDArr &data);
        //high_1_hz(data)
        oneDArr high_1_hz(oneDArr &data);

    private:
        axesArr filter(axesArr &data,COEFFICIENTS &coefficients);  
        oneDArr filter(oneDArr &data,COEFFICIENTS &coefficients);

};