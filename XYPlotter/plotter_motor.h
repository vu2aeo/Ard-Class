#ifndef PLOTTER_MOTOR
#define PLOTTER_MOTOR

#include "Arduino.h"
#define STEPS_PER_FULL_TURN 4096

class PlotterMotor
{
  private:
  
  int curStep;
  boolean turnRight;
  float angleNow;
  
  //pin Allocations
  
  byte pinA, pinB, pinC, pinD;
  
  float stepDelay;
  
  void StepMotor();
  
  public:
  
  PlotterMotor(byte, byte, byte, byte, float, float);
  
  void SetAngle(float);
  
//  void GoToAngle(float); 
  
  float GetAngle();
  
  void SetTurnRight(boolean);  
    
  void TurnOffPins();
  
  void StepOnce();
};

PlotterMotor::PlotterMotor(byte pA, byte pB, byte pC, byte pD, float d, float a)
{
  //designate Pins and set to output
  
  pinA = pA; pinMode(pinA, OUTPUT);
  
  pinB = pB; pinMode(pinB, OUTPUT);
  
  pinC = pC; pinMode(pinC, OUTPUT);
  
  pinD = pD; pinMode(pinD, OUTPUT);

  TurnOffPins();//turn off all Pins
  
  stepDelay = d;//set step delay
  
  SetAngle(a);//set startup angle
  
}

void PlotterMotor::SetAngle(float a)
{
  angleNow = a;
}

float PlotterMotor::GetAngle()
{
  return angleNow / STEPS_PER_FULL_TURN  *360;
}

void PlotterMotor::TurnOffPins()
{
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  delayMicroseconds(stepDelay);
}

void PlotterMotor::StepOnce()
{

    if (turnRight) 
    {
      curStep++;
      angleNow++;
    } 
    else 
    {
      curStep--;
      angleNow--;
    }
    
    if (curStep > 7) curStep = 0;
    
    if (curStep < 0) curStep = 7;
    
    switch(curStep)
    {
      case 0:
      
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, HIGH);
        
          break;
      
      case 1:
      
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, HIGH);
      
          break;
      
      case 2:
      
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
      
          break;
      
      case 3:
      
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
      
          break;
      
      case 4:
      
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
      
          break;
      
      case 5:
      
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
      
          break;
      
      case 6:
      
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
      
          break;
      
      case 7:
      
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, HIGH);
      
          break;
      
      default:
        
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
      
          break;
          
     
    }
    
    delayMicroseconds(stepDelay * 1000);//wait a moment to allow the shaft to move
  
}

void PlotterMotor::SetTurnRight(boolean turn)
{
  if(turn)
  {
    turnRight = true;
  } else turnRight = false;
}
#endif
