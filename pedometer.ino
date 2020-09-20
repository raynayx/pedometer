/*
pedometer glue

#########Button Screen Interaction #####################



#######################################################




*/
#include "UI.h"
#include "IMU.h"

#define accelerometerRange 2
#define accelerometerRate 50


// BUTTON SETUP; TWO BUTTONS: ONE FOR NAVIGATION; THE OTHER FOR SELECTION
const int navBtn = 8;
const int selBtn = 10;

int navBtnState;
int navBtnStateLast = LOW;

int selBtnState;
int selBtnStateLast = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup()
{
    Serial.begin(115200);
    
    pinMode(navBtn,INPUT);
    pinMode(selBtn,INPUT);

    setupSensor();
    
    setupScreen();
    welcomeScreen();
    

}

void loop()
{
  menu();
  
  int readNavBtn = digitalRead(navBtn);
  int readSelBtn = digitalRead(selBtn);
  
  if(readNavBtn)
  {
    delay(150);
    moveMenu(); 
    goHome();
  }
  if(readSelBtn)
  {
    delay(150);
    switchPage();
  }
  refreshPage();
    
}
