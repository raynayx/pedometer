#pragma once

#include "types.h"

class Filter
{
    public:
        COEFFICIENTS LOW_0_HZ ={{1, -1.979133761292768, 0.979521463540373},{0.000086384997973502, 0.000172769995947004, 0.000086384997973502}};
        COEFFICIENTS LOW_5_HZ = {{1, -1.80898117793047, 0.827224480562408},{0.095465967120306, -0.172688631608676, 0.095465967120306}};
        COEFFICIENTS HIGH_1_HZ = {{1, -1.905384612118461, 0.910092542787947},{0.953986986993339, -1.907503180919730, 0.953986986993339}};

    
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
