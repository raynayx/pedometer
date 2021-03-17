#include "analyzer.h"
// #define DEBUG

Analyzer::Analyzer(double* d)
{
    data = d;
}

unsigned long steps = 0;
void Analyzer::measureSteps()
{
    int lsteps = 0;  //number of steps for each set
    bool count_steps = true;

    for(int i = 0; i < maxSize; i++)
    {
        if(i != 0)
        {
            if((data[i] >= THRESHOLD) && (data[i-1] < THRESHOLD))
            {
                // next unless count_steps 
                if(!count_steps)
                    continue;

                lsteps++;
                count_steps = false;
            }
            if((data[i] < 0) && (data[i-1] >= 0))
                count_steps = true;

        } 
        
            
            #ifdef DEBUG
                Serial.print("lSteps\t");
                Serial.print(lsteps);
                Serial.print("\tSTEPS\t");
                Serial.println(steps);
            #endif
    }
     steps += lsteps;    //add current result to all previous  
}