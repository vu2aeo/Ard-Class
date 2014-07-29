#ifndef ROBOT_THUMB_H
#define ROBOT_THUMB_H

#include "Arduino.h"
#include "Servo.h"
#include "/home/vu2aeo/arduino-1.0.5/libraries/RobotFinger/robotfinger.h"

class RobotThumb
{
	private:
	
	Servo rotator;
	
	RobotFinger flexor;
	
	int maxRotate, minRotate;
	
	bool opposesAtMaxRotation;
	
	public:
	
	RobotThumb();
	
	~RobotThumb();
	
	void SetRotationParameters(int, int, int);
	
	void SetFlexorParameters(int, int, int);
	
	void SetFlexAndOppositionFlags(bool, bool);
	
	void RotateMax();
	
	void RotateMin();
	
	void FlexMax();
	
	void Relax();
	
	void Flex(int);
	
	bool Rotate(int);
	
	void RotateAndFlex(int, int);	
	
};

#endif //ROBOT_THUMB_H
