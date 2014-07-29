#include "robotfinger.h"

RobotFinger::RobotFinger(int pin, int max, int min, bool turnDir)
{
	maxFlex = max;
	
	minFlex = min;
	
	pinNo = pin;
	
	flexesAtMaxPos = turnDir;
	
	actuator.attach(pinNo);
}

RobotFinger::RobotFinger()
{
}

void RobotFinger::SetFlexesAtMaxPosFlag(bool flexPos)
{
	flexesAtMaxPos = flexPos;
}

void RobotFinger::SetParameters(int pin, int max, int min)
{
	maxFlex = max;
	
	minFlex = min;
	
	pinNo = pin;
	
	actuator.attach(pinNo);
}

RobotFinger::~RobotFinger()
{
}

void RobotFinger::FlexMax()
{
	if (flexesAtMaxPos == true)
	{
		actuator.write(maxFlex);
		
	} else actuator.write(minFlex);
}

bool RobotFinger::Flex(int percent)
{
	
    if (percent >= 0 && percent <=100)
    {
    		    int slew = (maxFlex - minFlex) * percent/100;
    
    		    int gotoAngle;
    		    
		   if (flexesAtMaxPos == true)
		   {
		   	gotoAngle = minFlex + slew;
		   } else
		   {
		   	gotoAngle = maxFlex - slew;
		   }
		   
		   actuator.write(gotoAngle);
		   
		   return true;
        
    } else return false;
}


void RobotFinger::Relax()
{
	if (flexesAtMaxPos == true)
	{
		actuator.write(minFlex);
		
	} else actuator.write(maxFlex);
}



