#pragma once
#include <Arduino.h>
void calibrateAccel();
void setupSensor(); // setup the range and other params of sensor
unsigned long countStep();    // step counting algorithm

struct axes{float x; float y; float z;};

axes printAccel();

// find max value for each axis
axes maxVal(axes arr[50]);

//find min value for each axis
axes minVal(axes arr[50]);


//find max axis overall
float maxAxis (axes a);

// delay; supply interval in milliseconds
void myWait(int interval);
void testInterrupt();
void intTest2();
void intTest3();
void configureLSM9DS1Interrupts();
