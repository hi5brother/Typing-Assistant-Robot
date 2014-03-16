//Daniel Kao
//Mar 14, 2014
//Two-Line Follower

/*
the first line that it passes, it will ignore
after first occurrence, the robot will rotate by __ degrees each time it senses a line colour

*/

#define ROTATESCALE 2.06 //found from trial and error
#define EARLYSTOPFACTOR 0.30 //stop earlier to account for inertia

#define RMOTOR 1
#define LMOTOR 2

#define LIGHT 2

#define COLOUR1 25	//this is the colour of the line
#define COLOUR2 50

#define MAX 10

int zigrotate (int speed, int degrees, int lightTarget);
void followLine(int direction, int &bump);



int zigrotate (int speed, int degrees, int lightTarget){
	int neededCount, actualCount;
	int colourRange[64];
	int i;
	int light;
	int onTarget=1;
	
	SensorType[LIGHT]=sensorLightActive;
	nMotorPIDSpeedCtrl[LMOTOR]=mtrSpeedReg;
	nMotorPIDSpeedCtrl[RMOTOR]=mtrSpeedReg;
	if (degrees>0)
	{	//turns left
		nMotorEncoder[RMOTOR]=0;
		motor[RMOTOR]=SPEED;
		motor[LMOTOR]=-SPEED;
	}
	else 
	{	//turns right
		nMotorEncoder[LMOTOR]=0;
		motor[RMOTOR]=-SPEED;
		motor[LMOTOR]=SPEED;
	}
	
	neededCount=abs(degrees)*ROTATESCALE;
	actualCount=0;
	
	while (actualCount<(neededCount-SPEED*EARLYSTOPFACTOR))
	{
		light=SensorValue[LIGHT];
		
		for (i=0;i<=MAX;i++)
		{
			if (light==colourRange[i])
			{
				onTarget=1;
				nxtDisplayTextLine(7,"BREAK: %d",colourRange[i]);
				degrees=0;
				neededCount=abs(degrees)*ROTATESCALE;
				return 1;
			}
		}
		
		wait1Msec(1);
		
		if (neededCount>0)
			actualCount=nMotorEncoder[RMOTOR];        
		else if (neededCount<0)
			actualCount=nMotorEncoder[LMOTOR];
		else 
			break;
	}
	
	motor[RMOTOR]=SPEED;
	motor[LMOTOR]=SPEED;
	wait1Msec(100);
}