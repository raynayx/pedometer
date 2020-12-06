#pragma once
#include "types.h"

class Processor
{
    public:
        oneDArr dproduct;
        oneDArr filtered_data;
        parsedAxesArr parsedData;
        Processor(parsedAxesArr pdata);
        axesArr run(parsedAxesArr pdata);

    private:
        // dot_product of all the axes
        oneDArr dot_product();
        // filter the 1D data from the dot_product 
        oneDArr filter();

};