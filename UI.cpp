#include "UI.h"

// OLED over SPI
#define PIN_RESET 4 
#define PIN_DC    3  
#define PIN_CS    5

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
    oled.println("PEDOMETER");
    oled.println("v 0.0.1");
    oled.println("2020");
    oled.display();
    oled.setCursor(0,0);
    delay(1500);
    
}

void menu()
{
     if (currentPage != page::home)
      return;
     switch (selection)
    {
      case menuItem::steps:
        oled.clear(PAGE);
        oled.rect(0, 0, LCDWIDTH,11);
        oled.setCursor(4,2);
        oled.println("STEPS");
        oled.setCursor(4,12);
        oled.println("RAWDATA");
        oled.setCursor(4,22);
        oled.println("OFF");
        oled.display(); 
        
        break;


     case menuItem::rawData:
        oled.clear(PAGE);
        oled.setCursor(4,2);
        oled.println("STEPS");
        oled.rect(0, 10, LCDWIDTH,11);
        oled.setCursor(4,12);
        oled.println("RAWDATA");
        oled.setCursor(4,22);
        oled.println("OFF");
        oled.display(); 
    
        break;

    case menuItem::off:
        oled.clear(PAGE);
        oled.setCursor(4,2);
        oled.println("STEPS");
        oled.setCursor(4,12);
        oled.println("RAWDATA");
        oled.rect(0, 20, LCDWIDTH,11);
        oled.setCursor(4,22);
        oled.println("OFF");
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

void stepsPage()
{
  oled.clear(PAGE);
        oled.rect(0, 0, LCDWIDTH,LCDHEIGHT);
        oled.setCursor(2,2);
        oled.println("No. of");
        oled.setCursor(2,10);
        oled.println("STEPS:");
        oled.setCursor(2,20);
        oled.println(124);
        oled.display(); 
}


void rawDataPage()
{
        oled.clear(PAGE);
        oled.rect(0, 0, LCDWIDTH,LCDHEIGHT);
        oled.setCursor(2,2);
        oled.println("A: x, y, z");
        oled.setCursor(2,10);
        oled.print("   ");
        oled.print(2);
        oled.print(", ");
        oled.print(5);
        oled.print(", ");
        oled.print(1);
        oled.display(); 
}

void switchPage()
{
      if(selection == menuItem::steps)
      {
        // switch to steps page
        currentPage = page::steps;
        stepsPage();
      }
      else if(selection == menuItem::rawData)
      {
        // switch to raw data page
        currentPage = page::rawData;
        rawDataPage();
      }
      else
      {
        // remain on home menu
        currentPage = page::home;
      }
      
    
    
}

void goHome()
{
  if(currentPage == page::steps || currentPage == page::rawData )
  {
     menu();
     currentPage = page::home;
  }
  else
  {
    return;
  }
}
