#include "UI.h"
#include "IMU.h"

// OLED over SPI
#define PIN_RESET 9  //4 
#define PIN_DC    8  //3
#define PIN_CS    10  //5

MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS);

menuItem selection = menuItem::steps;           //home menu options
page currentPage = page::home;                  //page selected

void setupScreen()
{
  delay(100);
  oled.begin();
  oled.clear(PAGE); 
  oled.clear(ALL);
}

void welcomeScreen()
{
    Serial.println(F("PEDO"));
    oled.println(F("PEDOMETER"));
    oled.println(F("v 0.0.1"));
    oled.println(F("2020"));
    oled.display();
    oled.setCursor(0,0);
    delay(1500);
    
}

void menu()
{
     String steps = F("STEPS");
     String raw_data = F("RAW DATA");
     String help = F("HELP");
     
     if (currentPage != page::home)
      return;
     switch (selection)
    {
      case menuItem::steps:
        oled.clear(PAGE);
        oled.rect(0, 0, LCDWIDTH,11);
        oled.setCursor(4,2);
        oled.println(steps);
        oled.setCursor(4,12);
        oled.println(raw_data);
        oled.setCursor(4,22);
        oled.println(help);
        oled.display(); 
        
        break;


     case menuItem::rawData:
        oled.clear(PAGE);
        oled.setCursor(4,2);
        oled.println(steps);
        oled.rect(0, 10, LCDWIDTH,11);
        oled.setCursor(4,12);
        oled.println(raw_data);
        oled.setCursor(4,22);
        oled.println(help);
        oled.display(); 
    
        break;

    case menuItem::off:
        oled.clear(PAGE);
        oled.setCursor(4,2);
        oled.println(steps);
        oled.setCursor(4,12);
        oled.println(raw_data);
        oled.rect(0, 20, LCDWIDTH,11);
        oled.setCursor(4,22);
        oled.println(help);
        oled.display(); 
    
        break;     
      

        
    }
  
    // home screen setup
   
      
    
    
}

void moveMenu()
{
  if(selection == menuItem::steps)
  {
    selection = menuItem::rawData;
  }
  else if(selection == menuItem::rawData)
  {
    selection = menuItem::off;
  }
  else if(selection == menuItem::off)
  {
    selection = menuItem::steps; 
  }
}

void stepsPage(long steps)
{
  oled.clear(PAGE);
        oled.rect(0, 0, LCDWIDTH,LCDHEIGHT);
        oled.setCursor(2,2);
        oled.println(F("No. of"));
        oled.setCursor(2,10);
        oled.println(F("STEPS:"));
        oled.setCursor(2,20);
        oled.println(steps);
        oled.display(); 
}


void rawDataPage(float x, float y, float z)
{
        oled.clear(PAGE);
        oled.rect(0, 0, LCDWIDTH,LCDHEIGHT);
        oled.setCursor(2,2);
        oled.println(F("Accel"));
        oled.setCursor(2,10);
        oled.print(F("x "));
        oled.println(x);
        oled.setCursor(2,20);
        oled.print(F("y "));
        oled.println(y);
        oled.setCursor(2,30);
        oled.print(F("z "));
        oled.println(z);
        oled.display(); 
}

void switchPage()
{
      if(selection == menuItem::steps)
      {
        // switch to steps page
        currentPage = page::steps;
        stepsPage(countStep());
        
      }
      else if(selection == menuItem::rawData)
      {
        // switch to raw data page
        currentPage = page::rawData;
        refreshPage(); 
        
      }
      else
      {
        // remain on home menu
        currentPage = page::home;
      }
      
    
    
}
 void refreshPage()
{
    axes a;
  if (currentPage == page::rawData)
  {
    a = printAccel();
    rawDataPage(a.x,a.y,a.z);
    Serial.println(F("page being refreshed"));
    Serial.print(a.x);
    Serial.print(a.y);
    Serial.print(a.z);
  }
  if (currentPage == page::steps)
  {
    stepsPage(countStep());
  }
}

void goHome()
{
  if(currentPage == page::steps || currentPage == page::rawData )
  {
     menu();
     currentPage = page::home;
  }
}

void screenOff()
{
  oled.command(DISPLAYOFF);
}

void screenOn()
{
  oled.command(DISPLAYON);
}