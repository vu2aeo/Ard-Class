#ifndef ROBOT_FINGER_H
#define ROBOT_FINGER_H

#include "Arduino.h"
#include <Servo.h>

class RobotFinger
{
	private:
	
	Servo actuator;
	
	int pinNo;
	
	bool flexesAtMaxPos;
	
	int maxFlex;
	
	int minFlex;
	
	public:
	
	RobotFinger(int, int, int, bool);
	
	RobotFinger();
	
	~RobotFinger();

	void SetParameters(int, int, int);
	
	void SetFlexesAtMaxPosFlag(bool);
	
	bool Flex(int);
	
	void FlexMax();
	
	void Relax();
};

#endif // ROBOT_FINGER_H

