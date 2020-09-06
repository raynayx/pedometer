#pragma once
#include <Wire.h>
#include "rgb_lcd.h" //Screen library replace with OLED part library
#include <Arduino.h>



void setupScreen();
void welcomeScreen();
void turnOff();
void turnOn();
void backlight();
