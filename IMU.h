#pragma once

void calibrateAccel();
void setupSensor(); // setup the range and other params of sensor
int countStep();    // step counting algorithm

struct axes{float x; float y; float z;};

axes printAccel();
