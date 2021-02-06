#include "processor.h"
#include "filter.h"
#include "types.h"
#include <Arduino.h>

#define VERIFY
Filter f;
Processor::Processor(struct parsedAxesArr pdata)
{
    parsedData = pdata;
}

oneDArr Processor::dot_product()
{
     
    for(int i = 0; i < 50; i++)
    {
        dproduct.oneDArr[i] =
        parsedData.uArr[i].x * parsedData.gArr[i].x +
        parsedData.uArr[i].y * parsedData.gArr[i].y +
        parsedData.uArr[i].z * parsedData.gArr[i].z;

        #ifdef VERIFY
        Serial.print("dot product \t");
        Serial.println(dproduct.oneDArr[i]);
        #endif
    }
    return dproduct;
    
}

oneDArr Processor::filter()
{
    // take out low freq
    filtered_data = f.low_0_hz(dproduct);
    // take out high freq
    filtered_data = f.high_1_hz(filtered_data);
    
    #ifdef VERIFY
    for(int i=0;i<50;i++)
    {
      Serial.print("filtered 1D\t");
      Serial.println(filtered_data.oneDArr[i]);
    }

    #endif
    
    return filtered_data;

}

oneDArr Processor::run()
{
    // find dot product
    dot_product();
    return filter();
    // filter in 1D
}
