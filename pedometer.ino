/*
pedometer glue

#########Button Screen Interaction #####################



#######################################################




*/
// #include <avr/sleep.h>
#include "UI.h"
#include "IMU.h"
#include "filter.h"

#define timeoutDelay 20000
//#define TEST_ASA
int c= 0;
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

// IMU myImuP;
void setup()
{
    Serial.begin(115200);
//    pinMode(testPinA0,OUTPUT);
    pinMode(navBtn,INPUT_PULLUP);
    pinMode(selBtn,INPUT_PULLUP);
    // myImuP.setupSensor();
//    imu.configureLSM9DS1Interrupts();
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

//#ifdef TEST_ASA
axesArr a;
axesArr res;
Filter f;
for(int i=0;i<50;i++)
a.arr[i]= {1,2,3};

res = f.low_5_hz(a);

Serial.println("here");
delay(1000);
Serial.println(res.arr[8].z);

//#endif
    
}
