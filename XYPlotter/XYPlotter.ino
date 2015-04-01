#include "XY_Plotter.h"

XYPlotter iken1(3,4,5,6,7,8,9,10, 0.8, 0, 0);

void setup()
{
  Serial.begin(38400);
}

void loop()
{
//  iken1.GoToXY(-200, -60);
//  delay(3000);
//  
//  iken1.GoToXY(200, 120);
//  delay(3000);
  
 
 if(Serial.available())
 {
   float x = Serial.parseFloat();
   float y = Serial.parseFloat();
   
   iken1.GoToXY(x,y);
 }
 
 while (Serial.read() != -1){}//empty serial buffer
  
}

