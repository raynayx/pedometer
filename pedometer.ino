/*
pedometer glue

#########Button Screen Interaction #####################



#######################################################




*/
#include "UI.h"
#include "IMU.h"

#define timeoutDelay 20000
// BUTTON SETUP; TWO BUTTONS: ONE FOR NAVIGATION; THE OTHER FOR SELECTION
const uint8_t navBtn = 7;
const uint8_t selBtn = 6;

bool navBtnLastState = HIGH;
bool selBtnLastState = HIGH;
bool navBtnState;
bool selBtnState;

unsigned long navLastDebounce = 0;
unsigned long selLastDebounce = 0;
unsigned long timeout = 0;
int debounceDelay = 50;

void setup()
{
    Serial.begin(115200);
    
    pinMode(navBtn,INPUT_PULLUP);
    pinMode(selBtn,INPUT_PULLUP);
    pinMode(A0,OUTPUT);

    setupSensor();
    configureLSM9DS1Interrupts();
    
    setupScreen();
    welcomeScreen();
    

}

void loop()
{
  digitalWrite(A0,LOW);
  // menu();
//  testInterrupt();
  
  // uint8_t readNavBtn = digitalRead(navBtn);
  // uint8_t readSelBtn = digitalRead(selBtn);
  
  // if(readNavBtn != navBtnLastState)
  // {
  //   navLastDebounce = millis();
  // }
  // if(readSelBtn != selBtnLastState)
  // {
  //   selLastDebounce = millis();
  // }

  // if((millis() - navLastDebounce) > debounceDelay)
  // {
  //   if(readNavBtn != navBtnState)
  //   {
  //     navBtnState = readNavBtn;

  //     if(navBtnState == LOW)
  //     {
  //       screenOn();
  //       moveMenu(); 
  //       goHome();
  //       timeout = millis();
  //     }
  //   }
  // }

  // if((millis() - selLastDebounce) > debounceDelay)
  // {
  //   if(readSelBtn != selBtnState)
  //   {
  //     selBtnState = readSelBtn;
  //     if(selBtnState == LOW)
  //     {
  //       screenOn();
  //       switchPage();
  //       timeout = millis();
  //     }
  //   }
  // }
  // navBtnLastState = readNavBtn;
  // selBtnLastState = readSelBtn;
  
  // refreshPage();
//  Serial.println(countStep());

// if((millis() - timeout) > timeoutDelay )
// {
//   screenOff();
// }
    
}
