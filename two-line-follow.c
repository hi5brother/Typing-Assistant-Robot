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



typedef int range[11];

int zigrotate (int speed, int degrees, int lightTarget);
void drive;
void rotate(int speed, int degrees,int zigged);
int scanLight(int lightTarget,range ColourRange);
void generateRange(int lightTarget, range colourRange);

task main(){


}

void generateRange(int lightTarget, range colourRange){
	int i;
	
	for (i=0;i<=11;i++)
	{
		colourRange[i]=lightTarget-MAX/2+i;	//sets the colour range to +/- 5 of the target light
	}
}

int scanLight(int lightTarget,range colourRange){		//this will be used every second to scan if it is on a colour
	int light;
	int hit=0;
	
	SensorType[LIGHT]=sensorLightActive;
	
	light=SensorValue[LIGHT];
	
	for (i=0;i<=11;i++){
		if (light==colourRange[i]){
			hit=1;
			break;
		}
	}
	if (hit==1)
		return 1;		//returns 1 if it is on the colour
	else if (hit==0)
		return 0;
}

void rotate (int speed, int degrees){
	int neededCount, actualCount;
    
    if (degrees>0){
        nMotorEncoder[RMOTOR]=0; //zero right encoder
        motor[RMOTOR]=SPEED;
        motor[LMOTOR]=-SPEED;
    }
    else{
        nMotorEncoder[LMOTOR]=0; //zero left encoder
        motor[RMOTOR]=-SPEED;
        motor[LMOTOR]=SPEED;
    }
    
    neededCount=abs(degrees)*ROTATIONSCALE;
    actualCount=0;
    
    while(actualCount<(neededCount-SPEED*EARLYSTOPFACTOR)){
        wait1MSec(5);
        
        if (degrees>0)
            actualCount=nMotorEncoder[RMOTOR];
        else
            actualCount=nMotorEncoder[LMOTOR];
        }
    
    motor[RMOTOR]=0;
    motor[LMOTOR]=0;
    wait1Msec(200);

}

void drive (int lightTarget, range colourRange){
	int i;
	int zigged=1;
	nMotorPIDSpeedCtrl[LMOTOR]=mtrSpeedReg;
	nMotorPIDSpeedCtrl[RMOTOR]=mtrSpeedReg;
	
	motor[RMOTOR]=SPEED;
	motor[LMOTOR]=SPEED;
	
	while (scanLight(lightTarget, colourRange)==0){
		motor[RMOTOR]=SPEED;
		motor[LMOTOR]=SPEED;
	}
	if (scanLight(lightTarget,colourRange)==1){
		zigged=zigged*(-1);
		switch (zigged){
			case 1:
				rotate(20,20);
				break;
			case -1:
				rotate(20,20);
				break;
		}
			
	}
}



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
}