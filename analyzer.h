#pragma once
#include "types.h"

class Analyzer
{
    public:
        float THRESHOLD = 0.09;
        struct oneDArr data;
        
        Analyzer(struct oneDArr d);
        int measure_steps();

    private:
        int steps;
};
