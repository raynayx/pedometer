#include "pipeline.h"


// IMU imu;
//sequence leading to step counts

IMU modelIMU;

void countSteps()
{   
    //get values from IMU into buffer
    // imu.fillCircularBuffer();

    modelIMU.fillCircularBuffer();


    //parser to condition
    Parser par;
    par.parse();


    //processor to process
    Processor pro;
    double* processed = pro.filter();

    //analyzer to count steps
    Analyzer analyzer(processed);

    analyzer.measureSteps();
}