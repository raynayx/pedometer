/*
pedometer glue

#########Button Screen Interaction #####################



#######################################################




*/
// #include <avr/sleep.h>
// #include "UI.h"
#include "pipeline.h"


#define timeoutDelay 20000
#define TEST_ASA
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

//uint8_t testPinA0 = A0;
//
//void testInt()
//{
//  digitalWrite(testPinA0,LOW);
////  ack();
//  detachInterrupt(digitalPinToInterrupt(3));
//}

//void wake()
//{
//  sleep_disable();
//  ack();
//  detachInterrupt(digitalPinToInterrupt(3));
//}

//void sleepNow()
//{
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//  noInterrupts();
//  sleep_enable();
//  attachInterrupt(digitalPinToInterrupt(3),wake,FALLING);
//  interrupts();
//  sleep_cpu();
//}


void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN,OUTPUT);
//    pinMode(testPinA0,OUTPUT);
    pinMode(navBtn,INPUT_PULLUP);
    pinMode(selBtn,INPUT_PULLUP);
    modelIMU.setupSensor();
    // imu.configureLSM9DS1Interrupts();
//    setupScreen();
//    welcomeScreen();   
    

}

void loop()
{
//  ADCSRA = 0;     //turn of ADC
//  checkInt();
  
//   menu();
//   // attachInterrupt(digitalPinToInterrupt(3),testInt,LOW);
  
//   uint8_t readNavBtn = digitalRead(navBtn);
//   uint8_t readSelBtn = digitalRead(selBtn);
  
//   if(readNavBtn != navBtnLastState)
//   {
//     navLastDebounce = millis();
//   }
//   if(readSelBtn != selBtnLastState)
//   {
//     selLastDebounce = millis();
//   }

//   if((millis() - navLastDebounce) > debounceDelay)
//   {
//     if(readNavBtn != navBtnState)
//     {
//       navBtnState = readNavBtn;

//       if(navBtnState == LOW)
//       {
//         screenOn();
//         moveMenu(); 
//         goHome();
//         timeout = millis();
//       }
//     }
//   }

//   if((millis() - selLastDebounce) > debounceDelay)
//   {
//     if(readSelBtn != selBtnState)
//     {
//       selBtnState = readSelBtn;
//       if(selBtnState == LOW)
//       {
//         screenOn();
//         switchPage();
//         timeout = millis();
//       }
//     }
//   }
//   navBtnLastState = readNavBtn;
//   selBtnLastState = readSelBtn;
  
//   refreshPage();
// //  Serial.println(countStep());

// if((millis() - timeout) > timeoutDelay )
// {
//   timeout = millis();
//   screenOff();
// //  sleepNow();

// }
//digitalWrite(testPinA0,HIGH);
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    delay(500);
    countSteps();

    #ifdef DEBUG
        Serial.print(F("Steps[CountSteps]\t"));
        Serial.println(steps);
    #endif
}
