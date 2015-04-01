#ifndef GOTO_STEPPER
#define GOTO_STEPPER

#include "Arduino.h"

class GoToStepper
{
  private:
  
  byte pinA, pinB, pinC, pinD;
  int delayTime;
      
  void stepA();
  void stepB();
  void stepC();
  void stepD();
  
  void TurnOffPins();
  
  void StepForward();
  
  void StepBackward();  
  
  public:
  
  float curPos, newPos;
  float motorResolution;
  
  GoToStepper(byte pinA,
              byte pinB,
              byte pinC,
              byte pinD,
              int delayTime,
              float pos,
              float motorResolution);
  
  void SetInitPos(float);
  
  void GoToPosition(float);
};


#endif

