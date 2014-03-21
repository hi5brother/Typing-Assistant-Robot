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

#define LIGHT 1

#define SPEED 100

#define COLOUR1 25	//this is the colour of the line
#define COLOUR2 50

#define MAX 11



typedef int range[MAX];

//int zigrotate (int speed, int degrees, int lightTarget);
void drive(int lightTarget, range colourRange);
void rotate(int speed, int degrees);
int scanLight(int lightTarget,range colourRange);
void generateRange(int lightTarget, range colourRange);

task main()
{
	int colours[11];
	int zigged=1;
	int lightTarget=50;
	
	SensorType[LIGHT]=sensorLightActive;
	generateRange(COLOUR1,colours);
	
	
	nMotorPIDSpeedCtrl[LMOTOR]=mtrSpeedReg;
	nMotorPIDSpeedCtrl[RMOTOR]=mtrSpeedReg;
	
	rotate(20,20);
	while (true)
	{
		while (scanLight(lightTarget, colours)==0)
		{
			drive(COLOUR2,colours);
		}
		
		wait1Msec(100);
		
		if (scanLight(lightTarget,colours)==1)
		{
			zigged=zigged*(-1);
			if(zigged==1)
				rotate(20,40);
			else if(zigged==-1)
				rotate(20,-40);
		}
		
	}
	
}

void generateRange(int lightTarget, range colourRange)
{
	int i;
	
	for (i=0;i<MAX;i++)
	{
		colourRange[i]=lightTarget-MAX/2+i;	//sets the colour range to +/- 5 of the target light
	}
}

int scanLight(int lightTarget,range colourRange)
{	//this will be used every second to scan if it is on a colour
	int light;
	int hit=0;
	int i;
	
	SensorType[LIGHT]=sensorLightActive;
	
	light=SensorValue[LIGHT];
	nxtDisplayTextLine(4,"Light: %d",light);
	
	for (i=0;i<MAX;i++)
	{
		if (light==colourRange[i])
		{
			hit=1;
			break;
		}
	}
	if (hit==1)
		return 1;		//returns 1 if it is on the colour
	else if (hit==0)
		return 0;
}

void rotate (int speed, int degrees)
{
	int neededCount, actualCount;
	
	if (degrees>0)
	{
		nMotorEncoder[RMOTOR]=0; //zero right encoder
		motor[RMOTOR]=SPEED;
		motor[LMOTOR]=-SPEED;
	}
	else
	{
		nMotorEncoder[LMOTOR]=0; //zero left encoder
		motor[RMOTOR]=-SPEED;
		motor[LMOTOR]=SPEED;
	}
	
	neededCount=abs(degrees)*ROTATESCALE;
	actualCount=0;
	
	while(actualCount<(neededCount-SPEED*EARLYSTOPFACTOR))
	{
		wait1Msec(5);
		
		if (degrees>0)
			actualCount=nMotorEncoder[RMOTOR];
		else
			actualCount=nMotorEncoder[LMOTOR];
	}
	
	motor[RMOTOR]=0;
	motor[LMOTOR]=0;
	wait1Msec(200);
	
}

void drive (int lightTarget, range colourRange)
{
	
	
	motor[RMOTOR]=SPEED;
	motor[LMOTOR]=SPEED;
	
	
	
}


/*

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
}*/
