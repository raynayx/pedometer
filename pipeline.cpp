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
    double dp[maxSize]; //dotproduct result from dotProduct()
    double filteredD[maxSize]; 

    pro.dotProduct(dp);
    pro.filter(dp,filteredD);

    //analyzer to count steps
    Analyzer analyzer(filteredD);

    analyzer.measureSteps();
}