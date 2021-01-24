#pragma once

#include "types.h"
#include <Arduino.h>
#include <SparkFunLSM9DS1.h> 



class IMU
{
    public:
    
        // IMU settings
        #define PRINT_CALCULATED
        //#define PRINT_RAW 
        #define PRINT_SPEED 250 // 250 ms between prints
        //static unsigned long lastPrint = 0; // Keep track of print time
        // INT2 ---- 2
        // INT1 ---- 3

//        IMU();
        
        //returns a set of 50 total acceleration values from IMU
        axesArr xlValues();

        void calibrateAccel();
        void setupSensor(); // setup the range and other params of sensor
        unsigned long countStep();    // step counting algorithm


        axes printAccel();

        // find max value for each axis
        axes maxVal(axes arr[50]);

        //find min value for each axis
        axes minVal(axes arr[50]);


        //find max axis overall
        float maxAxis (axes a);

        // delay; supply interval in milliseconds
        void myWait(int interval);

        void configureLSM9DS1Interrupts();
        void checkInt();
        void ack();

    private:
            // #################### Steps variables###########
        unsigned long steps = 0;   // number of steps
        axes stored_reading[50] = {0};
        uint8_t sampling_counter = 0; 
        float precision = 0.2;
        axes threshold = {0.3,0.3,0.3};
        float sample_new;
        float sample_old;
        unsigned long timeOfPreviousStep = 0;
        uint8_t interval = 0;
        //###################################

//        const uint8_t intPin = 3;

};
