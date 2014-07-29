#include "bomotorpair.h"

BOMotorPair::BOMotorPair(int p1, int p2, int p3, int p4, int p5, int p6)
{
    M1_pin1 = p1;

    M1_pin2 = p2;

    M1_PWMPin = p3;

    M2_pin1 = p4;

    M2_pin2 = p5;

    M2_PWMPin = p6;
}

BOMotorPair::~BOMotorPair()
{

}

void BOMotorPair::SetMoveDirection(int dir)
{
    moveDirection = dir;

    switch(moveDirection)
    {
        case forward: //Moving Forward

                //Set both motors to move in opposite directions

                //right motor moves CW

                digitalWrite(M1_pin1, HIGH);
                digitalWrite(M1_pin2, LOW);

                //left motor moves CCW

                digitalWrite(M2_pin1, LOW);
                digitalWrite(M2_pin2, HIGH);

                break;

        case backward: //Moving Forward

                //Set both motors to move in opposite directions

                //right motor moves CCW

                digitalWrite(M1_pin1, LOW);
                digitalWrite(M1_pin2, HIGH);

                //left motor moves CW

                digitalWrite(M2_pin1, HIGH);
                digitalWrite(M2_pin2, LOW);

            break;

        case right: //Turning Right

                //Set both motors to move in the opposite direction

                //right motor moves CCW

                digitalWrite(M1_pin1, LOW);
                digitalWrite(M1_pin2, HIGH);

                //left motor moves CCW

                digitalWrite(M2_pin1, LOW);
                digitalWrite(M2_pin2, HIGH);

            break;

        case left: //Turning Left

                //Set both motors to move in the opposite direction

                //right motor moves CW

                digitalWrite(M1_pin1, HIGH);
                digitalWrite(M1_pin2, LOW);

                //left motor moves CW

                digitalWrite(M2_pin1, HIGH);
                digitalWrite(M2_pin2, LOW);

            break;
	
    }
}

void BOMotorPair::SetMoveSpeed(int s)
{
    M1_Speed = s;
    M2_Speed = s;
}

void BOMotorPair::SetTurnSpeed(int s1, int s2)
{
    M1_Speed = s1;
    M2_Speed = s2;
}

void BOMotorPair::SetWheelSpeedDifferential(int s1, int s2)
{
    //To turn gently over a curve....

    if(M1_Speed + s1 >= LOWER_ANALOG_LIMIT && M1_Speed + s1 <= UPPER_ANALOG_LIMIT)
    {
        M1_Speed +=s1;
    }

    if(M2_Speed + s2 >= LOWER_ANALOG_LIMIT && M2_Speed + s2 <= UPPER_ANALOG_LIMIT)
    {
        M2_Speed +=s2;
    }

}

void BOMotorPair::Move()
{
    analogWrite(M1_PWMPin, M1_Speed);

    analogWrite(M2_PWMPin, M2_Speed);
}

void BOMotorPair::Stop()
{
    analogWrite(M1_PWMPin, LOWER_ANALOG_LIMIT);

    analogWrite(M2_PWMPin, LOWER_ANALOG_LIMIT);
}

void BOMotorPair::Move(int duration)
{
    Move();

    delay(duration * MILLI_MULTIPLIER);

    Stop();
}

void BOMotorPair::Accelerate(int factor, int steps, int accelRate)
{

    for (int i = 0; i < steps; i++)
    {
        if (M1_Speed + factor >= LOWER_ANALOG_LIMIT && M1_Speed + factor <= UPPER_ANALOG_LIMIT)
        {
            M1_Speed += factor;
        }

        if (M2_Speed + factor >= LOWER_ANALOG_LIMIT && M2_Speed + factor <= UPPER_ANALOG_LIMIT)
        {
            M2_Speed += factor;
        }

        Move();

        delay(accelRate);
    }
}

void BOMotorPair::Accelerate(int finalSpeed, int delayRate)
{
    int increment = 1;//we need to speed up

    if (finalSpeed < (M1_Speed + M2_Speed)/2)
    {
        increment = -1;//we need to slow down
    }

    while(abs(finalSpeed - (M1_Speed + M2_Speed)/2) > SPEED_TOLERANCE)
    {
        M1_Speed +=increment;
        M2_Speed +=increment;

        Move();

        delay(delayRate);
    }
}

void BOMotorPair::MoveWheelsIndependently(int leftSpd, int rightSpd)
{
	int r = map(abs(rightSpd),0,511,0,255);
	
	int l = map(abs(leftSpd),0,511,0,255);
	
	//LEFT MOTOR
	
	if (leftSpd < 0)
	{
		//turn CW
	
		digitalWrite(M1_pin1,HIGH);
		digitalWrite(M1_pin2,LOW);
	}
	else
	{
		//turn CCW
	
		digitalWrite(M1_pin1,LOW);
		digitalWrite(M1_pin2,HIGH);
	}
	
	//RIGHT MOTOR
	
	if (rightSpd < 0)
	{
		//turn CW
	
		digitalWrite(M2_pin1,HIGH);
		digitalWrite(M2_pin2,LOW);
	}
	else
	{
		//turn CCW
	
		digitalWrite(M2_pin1,LOW);
		digitalWrite(M2_pin2,HIGH);
	}
	
	analogWrite(M1_PWMPin, r);
	
	analogWrite(M2_PWMPin, l);
	
}




