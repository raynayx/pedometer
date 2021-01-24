#pragma once
#include "IMU.h"
#include "parser.h"
#include "processor.h"
#include "analyzer.h"
#include "filter.h"
#include "types.h"
#include <Arduino.h>

static IMU imu;
int countSteps();
