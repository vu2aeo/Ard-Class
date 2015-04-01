#include "goto_stepper.h"

GoToStepper::GoToStepper(byte a,
              byte b,
              byte c,
              byte d,
              int dT,
              float pos,
              float mR)
{
  pinA = a;
  pinB = b;
  pinC = c;
  pinD = d;
  delayTime = dT;
  curPos = pos;
  newPos = pos;
  motorResolution = mR;
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  TurnOffPins();
}

void GoToStepper::TurnOffPins()
{
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
}

void GoToStepper::stepA()
{
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
}

void GoToStepper::stepB()
{
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
}

void GoToStepper::stepC()
{
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
}

void GoToStepper::stepD()
{
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
}

void GoToStepper::StepForward()
{
  //Serial.print("StepForward...");
  stepA();
  delay(delayTime);
  stepB();
  delay(delayTime);
  stepC();
  delay(delayTime);
  stepD();
  delay(delayTime);  
}

void GoToStepper::StepBackward()
{
  //Serial.print("StepBackward...");
  stepD();
  delay(delayTime);
  stepC();
  delay(delayTime);
  stepB();
  delay(delayTime);
  stepA();
  delay(delayTime);  
}

void GoToStepper::SetInitPos(float c)
{
  curPos = c;
}

void GoToStepper::GoToPosition(float pos)
{
  newPos = pos;
  if(abs(curPos-newPos) >= motorResolution - 0.01 && newPos > curPos)
  {
    while(newPos > curPos)
    {
//      Serial.print("is turning...");
//      Serial.print("Forward...");
//      Serial.print("c=");
//      Serial.print(curPos);
//      Serial.print("n=");
//      Serial.println(newPos);
      StepForward();   //Go Forward 
      curPos += motorResolution; 
    }
    TurnOffPins();
    return;
  }
   
  else if (abs(curPos-newPos) >= motorResolution - 0.01 && newPos < curPos)
  {
    while(newPos < curPos)
    {
//        Serial.print("is turning...");
//        Serial.print("Backward...");
//        Serial.print("c=");
//        Serial.print(curPos);
//        Serial.print("n=");
//        Serial.println(newPos);
        StepBackward();//GoBackward
        curPos -= motorResolution;
    }
    TurnOffPins();
    return;
  }
}

