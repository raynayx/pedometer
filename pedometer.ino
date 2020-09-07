/*
pedometer glue


*/
#include "UI.h"
#include "IMU.h"

#define accelerometerRange 2
#define accelerometerRate 50

#define backlightTime 1000

const int upBtn = 4; 

void setup()
{
    setupScreen();
    Serial.begin(115200);
    // pinMode(upBtn,INPUT); //active low
    setupSensor(accelerometerRange,accelerometerRate);
    // calibrateAccel();

}

void loop()
{
//    welcomeScreen();
    countStep();
    //  delay(550);

    Serial.println();
    
     
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
