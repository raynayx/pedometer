#include "pipeline.h"

// get values from IMU
// call parser to condition
// call processor to process
// call analyzer to count steps



//sequence leading to step counts
int countSteps()
{
axesArr imuData;
Serial.println("FC");
//IMU data
for(int i=0;i<50;i++)
{
   if (lsm.accelAvailable())
  {
  lsm.readAccel();
  imuData.arr[i]= {lsm.calcAccel(lsm.ax),lsm.calcAccel(lsm.ay),lsm.calcAccel(lsm.az)};
  Serial.print(imuData.arr[i].x);
  Serial.print("\t");
  Serial.print(imuData.arr[i].y);
  Serial.print("\t");
  Serial.println(imuData.arr[i].z);
  
  }
}

// parse data from mixed into user xl and gravity xl
Parser parser(imuData);
parsedAxesArr pAxesArr = parser.run();
Serial.println(pAxesArr.uArr[5].x);
Serial.println(pAxesArr.gArr[5].x);
// process from 3d into 1d
Processor processor(pAxesArr);
oneDArr processed = processor.run();

//call analyzer to count steps
Analyzer analyzer(processed);
int totalSteps = analyzer.measure_steps();
Serial.print("IN PIPELINE STEPS=");
Serial.println(totalSteps);
return totalSteps;
}
