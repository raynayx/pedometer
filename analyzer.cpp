#include "analyzer.h"
#include "types.h"

Analyzer::Analyzer(struct oneDArr d)
{
    data = d;
}


Analyzer::measure_steps()
{
    steps = 0;
    bool count_steps = true;

    for(int i = 0; i < 50; i++)
    {
        if (i != 0)
        {
            if((data.oneDArr[i] >= THRESHOLD) && (data.oneDArr[i-1] < THRESHOLD))
            {
                //next unless count_steps #####****####
                if(!count_steps)
                    continue;
                steps++;
                count_steps = false;
            }
            if((data.oneDArr[i] < 0) && (data.oneDArr[i-1] >= 0))
                count_steps = true;
        }

        
    }

    return steps;
}
