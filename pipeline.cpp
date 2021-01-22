#pragma once
//#include "IMU.h"
#include "parser.h"
#include "processor.h"
#include "analyzer.h"
#include "filter.h"
#include "types.h"



// get values from IMU
// call parser to condition
// call processor to process
// call analyzer to count steps

//sequence leading to step counts
int countSteps()
{
axesArr imuData;
Serial.println("FROM COUNT STEPS");
// dummy IMU data
for(int i=0;i<50;i++)
imuData.arr[i]= {1,2,3};


// parse data from mixed into user xl and gravity xl
Parser parser(imuData);
parsedAxesArr pAxesArr = parser.run();

// process from 3d into 1d
Processor processor(pAxesArr);
oneDArr processed = processor.run();

//call analyzer to count steps
Analyzer analyzer(processed);
int totalSteps = analyzer.measure_steps();

return totalSteps;
}

/*
int countSteps()
{
    //IMU imu;
	/*
    axesArr a = imu.xlValues();
	
		for (int i; i < 50; i++)
    {
        Serial.println(a.arr[i].x);
        Serial.println(a.arr[i].y);
        Serial.println(a.arr[i].z);
    }
	*/
    
//    return 1;
//}
