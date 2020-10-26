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
const uint8_t navBtn = 2;
const uint8_t selBtn = 3;

uint8_t navBtnState;
uint8_t navBtnStateLast = LOW;

uint8_t selBtnState;
uint8_t selBtnStateLast = LOW;

//unsigned long lastDebounceTime = 0;
//unsigned long debounceDelay = 50;

void setup()
{
    Serial.begin(115200);
    
    pinMode(navBtn,INPUT_PULLUP);
    pinMode(selBtn,INPUT_PULLUP);

    setupSensor();
    
    setupScreen();
    welcomeScreen();
    

}

void loop()
{
  menu();
  
  uint8_t readNavBtn = digitalRead(navBtn);
  uint8_t readSelBtn = digitalRead(selBtn);
  
  if(!readNavBtn)
  {
    delay(150);
    moveMenu(); 
    goHome();
  }
  if(!readSelBtn)
  {
    delay(150);
    switchPage();
  }
  refreshPage();
  Serial.println(countStep());
    
}
