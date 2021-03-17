#ifndef ANALYZER_H_
#define ANALYZER_H_

#include "types.h"


class Analyzer
{
    public:
      double* data;

      Analyzer (double* d);
      void measureSteps();  
};




#endif