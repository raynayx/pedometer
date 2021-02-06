#include <CircularBuffer.h>
#include "pipeline.h"


// get values from IMU
// call parser to condition
// call processor to process
// call analyzer to count steps

CircularBuffer<axes,50> buffer;

//sequence leading to step counts
int countSteps()
{
axesArr imuData;
//IMU data
for(int i=0;i<50;i++)
{
   if (lsm.accelAvailable())
  {
  lsm.readAccel();
  axes temp;
//  imuData.arr[i]= {lsm.calcAccel(lsm.ax),lsm.calcAccel(lsm.ay),lsm.calcAccel(lsm.az)};
  temp.x = lsm.calcAccel(lsm.ax);
  temp.y = lsm.calcAccel(lsm.ay);
  temp.z = lsm.calcAccel(lsm.az);
  
  buffer.push(temp);

  
  }
}
for(int i = 0; i < 50; i++)
{

  imuData.arr[i] = {buffer[i].x,buffer[i].y,buffer[i].z};
  Serial.print("data num:\t");
  Serial.print(i);
  Serial.print("\t");
  Serial.print(imuData.arr[i].x);
  Serial.print("\t");
  Serial.print(imuData.arr[i].y);
  Serial.print("\t");
  Serial.println(imuData.arr[i].z);
}

// parse data from mixed into user xl and gravity xl
Parser parser(imuData);
parsedAxesArr pAxesArr = parser.run();
for(int i=0;i<50;i++)
{
  Serial.print("parsed: \t");
Serial.print(pAxesArr.uArr[i].x);
Serial.print("\t");
Serial.print(pAxesArr.gArr[i].y);
Serial.print("\t");
Serial.println(pAxesArr.gArr[i].z);
}
// process from 3d into 1d
Processor processor(pAxesArr);
oneDArr processed = processor.run();
for(int i=0;i<50;i++)
{
  Serial.print("One D: \t");
  Serial.println(processed.oneDArr[i]);

}
//call analyzer to count steps
Analyzer analyzer(processed);
int totalSteps = analyzer.measure_steps();
Serial.print("IN PIPELINE STEPS=");
Serial.println(totalSteps);
return totalSteps;
}
