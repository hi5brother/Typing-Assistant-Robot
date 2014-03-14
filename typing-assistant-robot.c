//Daniel Kao and Christopher Ko
//APSC 142: Typing Assistant Robot
//March 2014

/*
#include "sound-function.c"
#include "on-screen-function.c"
#include "TouchSensor.c"
#include "LightSensor.c"
//#include "BackUp.c"
#include "Rotate.c"
#include "line-follow.c"
*/

#define RMOTOR 1
#define LMOTOR 2
#define RBUMP 0
#define LBUMP 3
#define LIGHT 1
#define MICROPHONE 3

// /* Other Definitions
#define COLOUR1 25
#define COLOUR2 50
#define COLOUR3 75
#define COLOUR4 100

#define SPEED 50
#define ZIGSPEED 20
#define ZIGZAG 10
#define MAX 64

#define ROTATESCALE 2.06 //found from trial and error
#define EARLYSTOPFACTOR 0.30 //stop earlier to account for inertia


#define ROWS 7
#define COLS 10

#define MAXHEIGHT 64
#define MAXWIDTH 100

#define MAXLINES 10

#define UPSIZE 4 //expands the pixel from 1 pixel to a square of 4x4 pixels

#define LEFT 30 //horizontal screen position at left edge of image
#define TOP 40 //vertical screen position at top edge of image

#define SOUNDTHRESH 65
#define AMBIENT 25

#define BACKSPEED 25
#define DURATION 2000
#define TONE 1100

#define DRIVESPEED 50


//typedef int rangeArray [MAX];		//gives a range of +/- 5 light values around the target level
void zigrotate (int speed, int degrees);
void followLine(int direction, int &bump);
void displayScreen (int spaceCount, int enterCount); //displays the number of spaces and enters that have been used
void clearScreen();		//clears the screen on call
void displaySmiley();		//displays a smiley somewhere random
void expand (int size, int clear, int initX, int initY);	//expands the selected pixel to a square of lengths /size
void rotate(int speed, int degrees);
int listen();
void touchSensor(int direction, int &spaceCount, int &enterCount, int &consecEnter);
void BackUp();
int lightSensor(int sound);



task main()
{
    int sound,direction;
    int spaceCount, enterCount, consecEnter;
    //Turn on speed regulation for accurate tracking
    nMotorPIDSpeedCtrl[RMOTOR]=mtrSpeedReg;
    nMotorPIDSpeedCtrl[LMOTOR]=mtrSpeedReg;

    //Turn on touch sensors for bumpers
    SensorType[RBUMP]=sensorTouch; //right
    SensorType[LBUMP]=sensorTouch; //left

    //Define the light sensor type on port S2
    SensorType[LIGHT]=sensorLightActive;

    //Sound
    SensorType[MICROPHONE]=sensorSoundDBA;

    while(true){
    	sound=listen();
   		nxtDisplayBigTextLine(4,"HI");
    	direction=lightSensor(sound);
    	touchSensor(direction,spaceCount,enterCount,consecEnter);
    	displayScreen(spaceCount,enterCount);
    	clearScreen();
    	displaySmiley();
  }
}

void followLine (int direction, int&bump) {
	int i;
	int light;
	int lightTarget;		//value of the colour that the bot is suppose to follow
	int onTarget;		//1 or 0, depending on whether the bot is on or not
	int zigged;
	int colourRange[MAX];


	if (direction==0)
		lightTarget=COLOUR1;
	else if (direction==1)
		lightTarget=COLOUR2;

	for (i=0;i<=10;i++){
		colourRange[i]=lightTarget-10/2+i;	//sets the colour range to +/- 5 of the target light
	}


	SensorType[LIGHT]=sensorLightActive;
	nMotorPIDSpeedCtrl[LMOTOR]=mtrSpeedReg;
	nMotorPIDSpeedCtrl[RMOTOR]=mtrSpeedReg;

	motor[RMOTOR]=ZIGSPEED;
	motor[LMOTOR]=ZIGSPEED;

	while (true){
		light=SensorValue[LIGHT];

		onTarget=0;		//each time through the while loop, it must check whether it is within the range
		for (i=0;i<=MAX;i++){
			if (light==colourRange[i])
				onTarget=1;
		}

		if (onTarget==0){		//not on the target colour
			if (zigged==1){	//zigged left last time
				zigrotate(ZIGSPEED, ZIGZAG);	//zag right
				zigged=0;
			}
			else if (zigged==-1){	//zigged right last time
				zigrotate(ZIGSPEED,-ZIGZAG);	//zag left
				zigged=1;
			}
		}
		else if (onTarget==1){		//on the target colour
			//drive forward
		}

		//touch sensor check


}
}

void zigrotate(int speed, int degrees){
	int neededCount, actualCount;

	if (degrees>0){	//turns left
		nMotorEncoder[RMOTOR]=0;
		motor[RMOTOR]=ZIGSPEED;
		motor[LMOTOR]=-ZIGSPEED;
	}
	else {	//turns right
		nMotorEncoder[LMOTOR]=0;
		motor[RMOTOR]=-ZIGSPEED;
		motor[LMOTOR]=ZIGSPEED;
	}

	neededCount=abs(degrees)*ROTATESCALE;
	actualCount=0;

	while (actualCount<neededCount-(ZIGSPEED*EARLYSTOPFACTOR)){
		wait1Msec(5);

		if (degrees>0){
			actualCount=nMotorEncoder[RMOTOR];
		}
        else
            actualCount=nMotorEncoder[LMOTOR];
        }

    motor[RMOTOR]=0;
    motor[LMOTOR]=0;



}

void displayScreen (int spaceCount, int enterCount){
	nxtDisplayTextLine (2, "Number of Spaces: %d", spaceCount);
	nxtDisplayTextLine (3, "Number of Enters: %d", enterCount);

}

void clearScreen(){		//clears the screen on call
	int i;
	for (i=0; i<MAXLINES;i++){
		nxtDisplayClearTextLine(i);
	}
}

void displaySmiley(){		//displays a smiley somewhere random
	int i, j; //row and column
	int x, y; //screen x and y coordinates
	int a,b; //start coordinates of the smiley

	byte image[ROWS][COLS]=
			{	{1,1,1,0,0,0,0,1,1,1},
				{1,1,0,0,0,0,0,0,1,1},
				{1,1,0,1,0,0,1,0,1,1},
				{1,1,0,0,0,0,0,0,1,1},
				{1,1,0,1,1,1,1,0,1,1},
				{1,1,0,0,1,1,0,0,1,1},
				{1,1,1,0,0,0,0,1,1,1},
			};

	a=random(MAXWIDTH-(COLS*UPSIZE));	//places the smiley at a random spot
	b=random(MAXHEIGHT-(ROWS*UPSIZE))+(ROWS*UPSIZE);

	for(i=0; i<=ROWS-1; i++)
	{
		for(j=0; j<=COLS-1; j++)
		{
			x = a+j*UPSIZE; //set x screen position according to the column value
			y = b-i*UPSIZE; //set y screen position according to the row value

			if(image[i][j] == 1)	//these pixels are empty
				expand (UPSIZE,1,x,y);
			else if(image[i][j] == 0)	//these pixels are filled
				expand (UPSIZE,0,x,y);

		}
		wait10Msec(20);
	}
	//wait10Msec(200);//delay end of program so we can image on the screen
}

void expand (int size, int clear, int initX, int initY)	//expands the selected pixel to a square of lengths /size
{
	int i;
	int j;
	if (clear==1)
	{
		for (i=0;i<size;i++)
		{
			for (j=0;j<size;j++)
				nxtClearPixel(initX+i,initY-j);		//(initX,initY) is the top left pixel)
		}
	}
	else if (clear==0)
	{
		for (i=0;i<size;i++)
		{
			for (j=0;j<size;j++)
				nxtSetPixel(initX+i,initY-j);
		}
	}
}


void rotate(int speed, int degrees){
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

    neededCount=abs(degrees)*ROTATESCALE;
    actualCount=0;

    while(actualCount<(neededCount-SPEED*EARLYSTOPFACTOR)){
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


int listen()
{
	int dBlevel;		//sound sensor level in decibels
	int sound;

	SensorType[MICROPHONE]=sensorSoundDBA;

	wait1Msec(500);		//wait 500msec to start recording

	while (true)
	{
		dBlevel=SensorValue[MICROPHONE];
		nxtDisplayTextLine(4,"%d",dBlevel);

		if (dBlevel>SOUNDTHRESH){	//returns a 1 if the sound is above 65 dB (SOUNDTHRESH)
			sound =1;
			break;
			}
		else if (dBlevel>AMBIENT){		//only returns something if sound is above the ambient room noise
			sound= 0;
			break;
		}
}
return sound;
}


void touchSensor(int direction, int &spaceCount, int &enterCount, int &consecEnter){
    int leftBump, rightBump;

    //Initialize Sensors
    leftBump=SensorValue[LBUMP];
    rightBump=SensorValue[RBUMP];

    if (leftBump==1 || rightBump==1){
        if (direction==0){
            spaceCount+=1;
            consecEnter=0;
            }
        else if (direction==1){
            enterCount+=1;
            consecEnter++;
            }
        }
        //Back away from the keyboard
        BackUp();
}

void BackUp(){
    int i, neededLoops;

    motor[RMOTOR]=-BACKSPEED;
    motor[LMOTOR]=-BACKSPEED;
    neededLoops=DURATION/500;

    for (i=0;i<neededLoops;i++){
        wait10Msec(20); //drive backwards for 200msecs
        PlayTone(TONE,30); //play 1100Hz tone for 30msecs
        wait10Msec(30); //drive backwards while waiting for tone to finish
    }

    motor[RMOTOR]=0;
    motor[LMOTOR]=0;
}
int lightSensor(int sound){
  int direction;
  int light; //current sensor light level

  motor[RMOTOR]=DRIVESPEED;
  motor[LMOTOR]=DRIVESPEED;

  while(true){


      light=SensorValue[LIGHT]; //get the new light sensor value
      if (light < COLOUR1){
          //Turn right
          direction=0;
          break;
          }
      else if  (light > COLOUR1 && light < COLOUR2){
          //Turn Left
          direction=1;
          break;
          }
      else if (light > COLOUR2 && light < COLOUR3){
          if (sound==1){
              //Backup a bit
              BackUp();
              //Turn Left
              }
          else if (sound==0){
              //Backup a bit
              BackUp();
              //Turn Right
              }
          }
      else if (light > COLOUR3 && light < COLOUR4){
          if (sound==1){
              //Backup a bit
              BackUp();
              //Turn Right
              }
          else if (sound==0){
              //Backup a bit
              BackUp();
              //Turn Left
              }
      }
    
}
return direction;
}
