/*
pedometer glue

#########Button Screen Interaction #####################



#######################################################




*/
#include "UI.h"
#include "IMU.h"


// BUTTON SETUP; TWO BUTTONS: ONE FOR NAVIGATION; THE OTHER FOR SELECTION
const uint8_t navBtn = 2;
const uint8_t selBtn = 3;

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
    myWait(100);
    if(!readNavBtn)
    {
      moveMenu(); 
      goHome();
    }
  }
  
  if(!readSelBtn)
  {
    myWait(100);
    if(!readSelBtn)
    {
      switchPage();
    }
  }
  
  refreshPage();
//  Serial.println(countStep());
    
}
