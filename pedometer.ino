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

bool navBtnLastState = HIGH;
bool selBtnLastState = HIGH;
bool navBtnState;
bool selBtnState;

unsigned long navLastDebounce = 0;
unsigned long selLastDebounce = 0;
int debounceDelay = 50;

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
  
  if(readNavBtn != navBtnLastState)
  {
    navLastDebounce = millis();
  }
  if(readSelBtn != selBtnLastState)
  {
    selLastDebounce = millis();
  }

  if((millis() - navLastDebounce) > debounceDelay)
  {
    if(readNavBtn != navBtnState)
    {
      navBtnState = readNavBtn;

      if(navBtnState == LOW)
      {
        moveMenu(); 
        goHome();
      }
    }
  }

  if((millis() - selLastDebounce) > debounceDelay)
  {
    if(readSelBtn != selBtnState)
    {
      selBtnState = readSelBtn;
      if(selBtnState == LOW)
      {
        switchPage();
      }
    }
  }
  navBtnLastState = readNavBtn;
  selBtnLastState = readSelBtn;
  
  refreshPage();
//  Serial.println(countStep());
    
}
