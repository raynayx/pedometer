#include "UI.h"


rgb_lcd show;
void setupScreen()
{
  show.begin(16,2);
}

void welcomeScreen()
{
    Serial.println("PEDOMETER");
    show.setCursor(3,0);
    show.setRGB(0,0,0);
    show.print("PEDOMETER");

    show.setCursor(1,1);
    show.print("(c)dXai 2020");
}

void turnOff()
{
  show.noDisplay();
  show.setRGB(0,0,0);
}  

void turnOn()
{
  show.display();
}

void backlight()
{
  show.setRGB(255,255,255);
  
}
