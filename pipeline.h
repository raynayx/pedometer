#pragma once
#include "IMU.h"
#include "parser.h"
#include "processor.h"
#include "analyzer.h"
#include "filter.h"
#include "types.h"
#include <Arduino.h>

extern IMU imu;
extern LSM9DS1 lsm;
int countSteps();
