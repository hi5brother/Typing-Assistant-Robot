//Daniel Kao and Christopher Ko
//APSC 142: Typing Assistant Robot
//March 20 2014

/*
This robot does something reall cool/useful/fun...
*/

//Define robot sensor port values
#define RMOTOR 1
#define LMOTOR 2

#define RBUMP 0
#define LBUMP 0

#define LIGHT 2

#define MICROPHONE 1

#define BULB 3


//Define light thresholds for the different boundaries

#define GREEN 35	//left
#define RED 31	//right
#define BLUE 100
#define YELLOW 40

//Define speeds
#define DRIVESPEED 20
#define RSPEED 5
#define BACKSPEED 5
#define DEGREE 110

//Define rotation values for robot
#define ROTATESCALE 2.75		//found from trial and error
#define EARLYSTOPFACTOR 0.2			//stop earlier to account for inertia

//For Colour Range
#define MAX 3

//Define smiley face parameters
#define ROWS 7
#define COLS 10
#define MAXHEIGHT 64
#define MAXWIDTH 100
#define MAXLINES 10
#define UPSIZE 4		//expands the pixel from 1 pixel to a square of 4x4 pixels
#define LEFT 30		//horizontal screen position at left edge of image
#define TOP 40		//vertical screen position at top edge of image

//Define sound parameters
#define SOUNDTHRESH 25
#define AMBIENT 15

//Define back up noises
#define DURATION 2000
#define TONE 1100


typedef int range[MAX]; //used for colourRange (colours that it checks over)

//Define function prototypes
//typedef int rangeArray [MAX];		//gives a range of +/- 5 light values around the target level

void sensorInitialize();
//Screen Functions
void displayScreen (int spaceCount, int enterCount, int consecEnter);		//displays the number of spaces and enters that have been used
void clearScreen();		//clears the screen on call
void displaySmiley();		//displays a smiley somewhere random
void expand (int size, int clear, int initX, int initY);		//expands the selected pixel to a square of lengths /size

//Basic Drive and Movement Functions
void rotate(int speed, int degrees);
void drive();
void BackUp(int direction);

//Inputs for Bumper, Sound, Light
int touchSensor(int direction, int &spaceCount, int &enterCount, int &consecEnter);
int listen();
int scanLight(range colourRange);

//Procedure Functions
void generateRange(int lightTarget, range colourRange);
int findKey(int key);
void reset(int &bumperHit, int &key, int &keyTarget, int &zigged);

task main()
{
		//int lightTarget=35;
		int key=0; // space = 1, enter = 2, indicates whether it has approached the right target, it is 0 when it is still looking
		int keyTarget=0; // space = 1, enter = 2, indicates which thing it is targetting

		int zigged;//determines which direction it ziggs next

		//sensor values
		int soundLevel;
		int light;

		//counter variables that will be showed onscreen
		int bumperHit=0;
		int spaceCount=0;
		int enterCount=0;
		int consecEnter=0;

		//range that the scanLight function will check
		range greenRange;	//left (towards space)
	  range redRange;	//right (towards enter)
	  range blueRange;	//top (towards keyboard)
	  range yellowRange; //back (idk man, edge of the world)
	  range targetRange;
		//generates the range
		generateRange(GREEN,greenRange);
	  generateRange(RED,redRange);
	  generateRange(BLUE,blueRange);
	  generateRange(YELLOW,yellowRange);

	  //START OF PROCEDURES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		while(consecEnter<2){
		  displayScreen(spaceCount,enterCount,consecEnter);
		  
		  soundLevel=listen();		//waits for the command (soft vs loud)
	  
			if (soundLevel==1){
				keyTarget=1;
				generateRange(GREEN,targetRange);
			}
			else if(soundLevel==0){
				keyTarget=2;
				generateRange(RED,targetRange);
			}
	
			//HARDCODE~~~~~~~~~~~~~~~~~
			keyTarget=2;
	
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~
			nxtDisplayTextLine(3,"KEY:%d",keyTarget);
			//MOVEMENT TOWARDS TARGET~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			while (key==0){
				key=findKey(keyTarget);	//keeps on driving until it finds the intended colour
				//wait10Msec(100);
				light=SensorValue[LIGHT];
			}
			clearScreen();
			nxtDisplayBigTextLine(2,"Found it");
	
			//ensures the robot drives past the first line 
			drive();
			wait1Msec(1000);
	
			//the robot finds the second line and then rotates
			while (scanLight(targetRange)==0)	{
				drive();
				//nxtDisplayBigTextLine(2,"ABOUT2ROTATE");
			}
	
			//different rotation cases based on whether it is going towards space or enter
			if (key==1){
				zigged=-1;	//first rotate will be to the right (rotate towards space)
				generateRange(GREEN,targetRange);
				rotate(DRIVESPEED,90*zigged);
			}
	
			else if (key==2){
				zigged=1;	//first rotate will be to the left (rotate towards enter)
				generateRange(RED,targetRange);
				rotate(DRIVESPEED,90*zigged);
			}
	
			//MOVEMENT WHILE TRACKING TOWARDS KEYBOARD~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			while (true) {
				clearScreen();
				//nxtDisplayBigTextLine(2,"ROTATING");
	
				//check whether the light is seen or bumper is hit
				while (scanLight(targetRange)==0 && bumperHit==0){	//driving straight when not rotating
					drive();
					bumperHit=touchSensor(keyTarget,spaceCount,enterCount,consecEnter);
				}
	
				//alternating zig zag movement
				if (scanLight(targetRange)==1){ 	//when it does not sense the necessary colours
					wait1Msec(100);
					zigged=zigged*(-1);	//switches the direction of the rotation each time it hits a colour
	
					if(zigged==1)
						rotate(RSPEED,DEGREE);
					else if(zigged==-1)
						rotate(RSPEED,-DEGREE);
				}
	
				//Procedure when bumper is hit
				if (bumperHit==1){
						clearScreen();
						nxtDisplayTextLine(1,"BUMPER HIT");
						motor[RMOTOR]=0;
			 			motor[LMOTOR]=0;
						
						displaySmiley();
						
						if(key==1)
							BackUp(-90);
						else if(key==2)
							BackUp(90);
						
						wait1Msec(1000);
						reset(bumperHit,key,keyTarget,zigged);
						break;
				}
	
			}
	}

}


int findKey(int key){	//

	int position; //1 is left, 2 is right, 3 is top, 4 is bottom

	range greenRange;	//left (towards space)
  range redRange;	//right (towards enter)
  range blueRange;	//top (towards keyboard)
  range yellowRange; //back (idk man, edge of the world)
  
	generateRange(GREEN,greenRange);
  generateRange(RED,redRange);
  generateRange(BLUE,blueRange);
  generateRange(YELLOW,yellowRange);
  
  while (scanLight(greenRange)!=0 || scanLight(redRange)!=0 || scanLight(blueRange)!=0||scanLight(yellowRange)!=0){
    	drive();	//keeps on driving until it hits a colour
	}

 	//finds the position of the robot depending on what colour it senses first
	if (scanLight(greenRange)==1)
		position=1;	//hit left barrier
	else if (scanLight(redRange)==1)
		position=2;	//hit right barrier
	else if (scanLight(blueRange)==1)
		position=3;	//hit top barrier
  else if (scanLight(yellowRange)==1)
		position=4; //hit bottom barrier

	//finds what to do	
	if (position==1 && key==1){
		//drive towards space
		//wait1Msec(100);
		return 1;
	}
	else if (position==1 && key==2){
		//turn around	
		clearScreen();
		nxtDisplayBigTextLine(1,"CANT FIND IT");

		rotate(RSPEED,180);

		return 0;
	}
	else if (position==2 && key==1){
		//turn around
		//wait10Msec(100);
		clearScreen();
		nxtDisplayBigTextLine(1,"CANT FIND IT");

		rotate(RSPEED,180);
		return 0;
	}
	else if (position==2 && key==2){
		//drive towards enter
		//wait1Msec(100);
		return 2;

	}
  else if (position==3 && key==1){
		//turn left
  	clearScreen();
		nxtDisplayBigTextLine(1,"CANT FIND IT");

  	rotate(RSPEED,-DEGREE);
  	return 0;
	} 
	else if (position==3 && key==2){
		//turn right
		clearScreen();
		nxtDisplayBigTextLine(1,"CANT FIND IT");

		rotate(RSPEED,DEGREE);
		return 0;
	} 
	else if (position==4 && key==1){
		//turn right
		clearScreen();
		nxtDisplayBigTextLine(1,"CANT FIND IT");

		rotate(RSPEED,DEGREE);
		return 0;
	} 
	else if (position==4 && key==2){
		//turn left
		clearScreen();
		nxtDisplayBigTextLine(1,"CANT FIND IT");

		rotate(RSPEED,-DEGREE);
		return 0;
	}
	return 0;
}

void generateRange(int lightTarget, range colourRange)
{
	int i;

	for (i=0;i<MAX;i++){
		colourRange[i]=lightTarget-MAX/2+i;	//sets the colour range to +/- 5 of the target light
	}
}


void sensorInitialize(){
	 nMotorPIDSpeedCtrl[RMOTOR]=mtrSpeedReg;
    nMotorPIDSpeedCtrl[LMOTOR]=mtrSpeedReg;
    SensorType[RBUMP]=sensorTouch;
    SensorType[LBUMP]=sensorTouch;
    SensorType[LIGHT]=sensorLightActive;
    SensorType[MICROPHONE]=sensorSoundDBA;	
}



void displayScreen (int spaceCount, int enterCount, int consecEnter){
	nxtDisplayTextLine (1, "# of Spaces: %d", spaceCount);
	nxtDisplayTextLine (2, "# of Enters: %d", enterCount);
	nxtDisplayTextLine (3, "ConsecEnter: %d", consecEnter);
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

	for(i=0; i<=ROWS-1; i++){
		for(j=0; j<=COLS-1; j++){
			x = a+j*UPSIZE; //set x screen position according to the column value
			y = b-i*UPSIZE; //set y screen position according to the row value

			if(image[i][j] == 1)	//these pixels are empty
				expand (UPSIZE,1,x,y);
			else if(image[i][j] == 0)	//these pixels are filled
				expand (UPSIZE,0,x,y);
		}
		wait10Msec(20);
	}
}

void expand (int size, int clear, int initX, int initY)	//expands the selected pixel to a square of lengths /size
{
	int i;
	int j;
	if (clear==1){
		for (i=0;i<size;i++){
			for (j=0;j<size;j++)
				nxtClearPixel(initX+i,initY-j);		//(initX,initY) is the top left pixel)
		}
	}
	else if (clear==0){
		for (i=0;i<size;i++){
			for (j=0;j<size;j++)
				nxtSetPixel(initX+i,initY-j);
		}
	}
}

int scanLight(range colourRange)
{	//this will be used every second to scan if it is on a colour
	int light;
	int hit=0;
	int i;

	SensorType[LIGHT]=sensorLightActive;
	drive();

	light=SensorValue[LIGHT];
	nxtDisplayTextLine(4,"Light: %d",light);

	for (i=0;i<MAX;i++){
		if (light==colourRange[i]){
			hit=1;
			break;
		}
	}
	if (hit==1)
		return 1;		//returns 1 if it is on the colour
	else if (hit==0)
		return 0;
	return 1;
}


void drive (){
	motor[RMOTOR]=DRIVESPEED;
	motor[LMOTOR]=DRIVESPEED;
}

void rotate (int speed, int degrees){
	int neededCount, actualCount;

	if (degrees>0){
		nMotorEncoder[RMOTOR]=0; //zero right encoder
		motor[RMOTOR]=speed;
		motor[LMOTOR]=-speed;
	}
	else{
		nMotorEncoder[LMOTOR]=0; //zero left encoder
		motor[RMOTOR]=-speed;
		motor[LMOTOR]=speed;
	}

	neededCount=abs(degrees)*ROTATESCALE;
	actualCount=0;

	while(actualCount<(neededCount-speed*EARLYSTOPFACTOR))
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


int touchSensor (int direction, int &spaceCount, int &enterCount, int &consecEnter){
	int leftBump, rightBump;

	//for some reason, the left bump shows 183 when hit, and right shows 184 when hit
	//its 1024 when not hit

 	//Initialize Sensors
  leftBump=SensorValue[LBUMP];
  rightBump=SensorValue[RBUMP];
	nxtDisplayTextLine(5,"LEFT %d",leftBump);
	nxtDisplayTextLine(6,"RIGHT %d",rightBump);
  
  if (leftBump==183 || rightBump==184){
  	nxtDisplayTextLine(2,"HIT");
      if (direction==0){
          spaceCount+=1;
          consecEnter=0;
         
          }
      else if (direction==1){
          enterCount+=1;
          consecEnter++;
          
          }
  	return 1;	//when the sensor is hit, display 1
  }
  else 
  	return 0;
}

void BackUp(int direction){
    int i, neededLoops;

    motor[RMOTOR]=-BACKSPEED;
    motor[LMOTOR]=-BACKSPEED;
    neededLoops=DURATION/500;

    for (i=0;i<neededLoops;i++){
        wait10Msec(20); //drive backwards for 200msecs
        PlayTone(TONE,30); //play 1100Hz tone for 30msecs
        wait10Msec(30); //drive backwards while waiting for tone to finish
    }
    
    rotate(BACKSPEED,direction);
    drive();
    wait1Msec(2000); //change this depending on where the placement of the tape is (time for it to reach somewhere in the centre of the box)
    motor[RMOTOR]=0;
    motor[LMOTOR]=0;
   	rotate(BACKSPEED,-direction);
}

void reset(int &bumperHit, int &key, int &keyTarget,int &zigged){
	bumperHit=0;
	key=0;
	keyTarget=0;
	zigged=1;
	clearScreen();
}
