#pragma once
#include "types.h"

class Analyzer
{
    public:
        float THRESHOLD = 0.09;
        struct oneDArr data;

        int steps;
        
        Analyzer(struct oneDArr d);


    private:
        int measure_steps();



};
