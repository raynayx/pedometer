/*
pedometer glue


*/
#include "UI.h"
#include "IMU.h"

#include "CurieIMU.h"

#define accelerometerRange 2
#define accelerometerRate 50

#define backlightTime 1000

const int upBtn = 4; 


boolean stepEventsEnabeled = false;   
long lastStepCount = 0;

void setup()
{
    setupScreen();
    Serial.begin(115200);
    // pinMode(upBtn,INPUT); //active low
    setupSensor(accelerometerRange,accelerometerRate);
    // calibrateAccel();

    
    // from CurieIMU library
    CurieIMU.setStepDetectionMode(CURIE_IMU_STEP_MODE_NORMAL);
    // enable step counting:
    CurieIMU.setStepCountEnabled(true);

    if (stepEventsEnabeled) {
    // attach the eventCallback function as the
    // step event handler:
    CurieIMU.attachInterrupt(eventCallback);
    CurieIMU.interrupts(CURIE_IMU_STEP);  // turn on step detection

    Serial.println("IMU initialisation complete, waiting for events...");
  }

}

void loop()
{
//    welcomeScreen();
    countStep();
    //  delay(550);
    

    Serial.println();


     if (!stepEventsEnabeled) {
    updateStepCount();
  }
     
    // turnOff();
    // delay(10000);
    // turnOn();

    // if(upBtn == HIGH)
    // {
    //   Serial.println("pressed");
    //   backlight();
    //   // start coutdown to turnOff the light
    // }
    
}


static void eventCallback(void) {
  if (CurieIMU.stepsDetected())
    updateStepCount();
}

static void updateStepCount() {
  // get the step count:
  int stepCount = CurieIMU.getStepCount();

  // if the step count has changed, print it:
  if (stepCount != lastStepCount) {
    Serial.print("Step count: ");
    Serial.println(stepCount);
    // save the current count for comparison next check:
    lastStepCount = stepCount;
  }
}
