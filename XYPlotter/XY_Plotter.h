#include "plotter_motor.h"
#define MOTOR_ERROR 0.3

class XYPlotter
{
  private:
  
  PlotterMotor *XMotor, *YMotor;
    
  float curX, curY;
  
  public:
  
  XYPlotter(byte, byte, byte, byte, 
            byte, byte, byte, byte, 
            float, float, float);
  
  void SetXY(float, float);
  
  void GoToXY(float, float);
  
  float GetX();
  
  float GetY();
  
};

XYPlotter::XYPlotter(byte xA, byte xB, byte xC, byte xD,
                     byte yA, byte yB, byte yC, byte yD,
                    float mDelay, float pX, float pY)
{
  XMotor = new PlotterMotor(xA, xB, xC, xD, mDelay, pX);
  YMotor = new PlotterMotor(yA, yB, yC, yD, mDelay, pY);
 }

void XYPlotter::SetXY(float x, float y)
{
  XMotor->SetAngle(x);
  YMotor->SetAngle(y);
  
  curX = x;
  curY = y;

}

void XYPlotter::GoToXY(float x, float y)
{
  float errX = x - curX;
  
//  Serial.print("Er X:");
//  Serial.print(errX);
  
  if (errX > 0)
  {
    XMotor->SetTurnRight(true);
  } else XMotor->SetTurnRight(false);
  
  float errY = y - curY;
  
//  Serial.print("Er Y:");
//  Serial.print(errY);
  
  if (errY > 0)
  {
    YMotor->SetTurnRight(true);
  } else YMotor->SetTurnRight(false);
  
  //calc nStepsX and nStepsY
  
  int nStepsX, nStepsY;
  
  if(abs(errX) >= abs(errY))
  {
    nStepsX = round(abs(errX/errY));
    nStepsY = 1;
  } 
  else
  {
    nStepsY = round(abs(errY/errX));
    nStepsX = 1;
  }
  
  while (abs(errX) >= MOTOR_ERROR || abs(errY) >= MOTOR_ERROR)
  {
    //do a stepping sequence
    
    if(abs(errX) >= MOTOR_ERROR)
    {
      for(int i = 0; i < nStepsX; i++)
      {
        //step X motor one step
        
        XMotor->StepOnce();
      }
      
    }
    
    if(abs(errY) >= MOTOR_ERROR)
    {
      for(int i = 0; i < nStepsY; i++)
      {
        //step Y motor one step
        
        YMotor->StepOnce();
      }
      
    }
    
    //recalc the error
    
    curX = XMotor->GetAngle();
    curY = YMotor->GetAngle();
    
    errX = x - curX;
    errY = y - curY;
    
//   Serial.print("----------Step Over.......");
//   Serial.print(errX);
//   Serial.print(",");
//   Serial.println(errY);
  
   } // end of while loop

   //the turn is over
   
//   Serial.print("Turn Over.......");
//   Serial.print(curX);
//   Serial.print(",");
//   Serial.println(curY);
  
   XMotor->TurnOffPins();
   YMotor->TurnOffPins(); 

}

float XYPlotter::GetX()
{
  return curX;
}

float XYPlotter::GetY()
{
  return curY;
}



