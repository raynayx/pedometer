 /*


###############################OLED CONNECTIONS OVER SPI ############################################
      MicroOLED ------------- Arduino
      GND ------------------- GND
      VDD ------------------- 3.3V (VCC)
      D1/MOSI ----------------- D11 (don't change)
      D0/SCK ------------------ D13 (don't change)
      D2
      D/C ------------------- D8 (can be any digital pin)
      RST ------------------- D9 (can be any digital pin)
      CS  ------------------- D10 (can be any digital pin)
######################################################################################################



*/

#pragma once
#include <SPI.h> 
#include <SFE_MicroOLED.h>  //OLED Screen library 
#include <Arduino.h>

#include "pipeline.h"



enum class menuItem {steps,rawData,off};
enum class page {home,steps,rawData};
void setupScreen();
void welcomeScreen();
void menu();
void moveMenu();
void switchPage();
void refreshPage();
void goHome();
void screenOn();
void screenOff();
