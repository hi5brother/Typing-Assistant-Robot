//Daniel Kao
//Mar 13, 2014
//Line follower

/*
uses rotate function 
need to test this shit out

*/
#define ROTATESCALE 2.06 //found from trial and error
#define EARLYSTOPFACTOR 0.30 //stop earlier to account for inertia

#define SPEED 20
#define ZIGZAG 10

#define RMOTOR 1
#define LMOTOR 3

#define LIGHT 1

#define COLOUR1 25
#define COLOUR2 50

#define MAX 10

//YO ADD ME

typedef int rangeArray [MAX+1]		//gives a range of +/- 5 light values around the target level
void zigrotate (int speed, int degrees);
void followLine(int direction, int &bump);


void followLine (int direction, int&bump); {
	int i;
	int light;
	int lightTarget;		//value of the colour that the bot is suppose to follow
	int onTarget;		//1 or 0, depending on whether the bot is on or not
	int zigged;
	rangeArray colourRange;
	
	
	if (direction==0)
		lightTarget==COLOUR1;
	else if (direction==1)
		lightTarget==COLOUR2;
		
	for (i=0;i<=MAX;i++){
		colourRange[i]=lightTarget-MAX/2+i;	//sets the colour range to +/- 5 of the target light
	}
	
	
	SensorType[LIGHT]=sensorLightActive;
	nMotorPIDSpeedCtrl[LMOTOR]=mtrSpeedReg;
	nMotorPIDSpeedCtrl[RMOTOR]=mtrSpeedReg;
	
	motor[RMOTOR]=SPEED;
	motor[LMOTOR]=SPEED;
	
	while (true){
		light=SensorValue[LIGHT];
		
		onTarget=0		//each time through the while loop, it must check whether it is within the range
		for (i=0;i<=MAX;i++){
			if (light==colourRange[i])
				onTarget==1;
		}
		
		if (onTarget==0){		//not on the target colour
			if (zigged==1){	//zigged left last time
				zigrotate(SPEED, ZIGZAG);	//zag right 
				zigged==0;
			}
			else if (zigged==-1){	//zigged right last time
				zigrotate(SPEED,-ZIGZAG);	//zag left
				zigged=1;
			}	
		}
		else if (onTarget==1){		//on the target colour
			//drive forward
		}
		
		//touch sensor check
		
	
	
}

void zigrotate(int speed, int degrees){
	int neededCount, actualCount;
	
	if (degrees>0){	//turns left
		nMotorEncoder[RMOTOR]=0;
		motor[RMOTOR]=SPEED;
		motor[LMOTOR]=-SPEED;
	}
	else {	//turns right
		nMotorEncoder[LMOTOR]=0;
		motor[RMOTOR]=-SPEED;
		motor[LMOTOR]=SPEED;
	}
	
	neededCount=abs(degrees)*ROTATIONSCALE;
	actualCount=0;
	
	while (actualCount<neededCount-(SPEED*EARLYSTOPFACTOR)){
		wait1MSec(5);
		
		if (degrees>0){
			actualCount=nMotorEncoder[RMOTOR];        
		}
        else
            actualCount=nMotorEncoder[LMOTOR];
        }
    
    motor[RMOTOR]=0;
    motor[LMOTOR]=0;
			
	
	
}
    