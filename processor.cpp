#include "processor.h"
#include "filter.h"
#include "types.h"

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
    }
    return dproduct;
    
}

oneDArr Processor::filter()
{
    // take out low freq
    filtered_data = f.low_0_hz(dproduct);
    // take out high freq
    filtered_data = f.high_1_hz(filtered_data);

    return filtered_data;

}
