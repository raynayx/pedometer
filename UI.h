#pragma once
#include <SPI.h> 
#include <SFE_MicroOLED.h>  //OLED Screen library 
#include <Arduino.h>


class UI{
    enum class menuItem {steps,rawData,off};
    enum class page {home,steps,rawData};
    menuItem selection = menuItem::steps;           //home menu options
    page currentPage = page::home;                  //page selected

    public:
    
        
        void setupScreen();
        void welcomeScreen();
        void menu();
        void moveMenu();
        void switchPage();
        void refreshPage();
        void goHome();
        void screenOn();
        void screenOff();
        void errorLog(String &err);
        void stepsPage(long steps);
        void rawDataPage(float x, float y, float z);

};
