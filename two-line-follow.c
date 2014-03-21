//Daniel Kao and Christopher Ko
//APSC 142: Typing Assistant Robot
//March 20 2014

/*
This robot does something reall cool/useful/fun...
*/

//Define robot sensor port values
#define RMOTOR 2
#define LMOTOR 1

#define RBUMP 0
#define LBUMP 2

#define LIGHT 1

#define MICROPHONE 2

#define BULB 3

//Define light thresholds for the different boundaries

#define COLOUR1 25
#define COLOUR2 50
#define COLOUR3 75
#define COLOUR4 100

#define GREEN 40
#define RED 60
#define BLUE 20
#define YELLOW 30

//Define speeds
#define DRIVESPEED 5
#define RSPEED 5
#define BACKSPEED 5
#define DEGREE 100

//Define rotation values for robot
#define ROTATESCALE 2.06		//found from trial and error
#define EARLYSTOPFACTOR 0.30		//stop earlier to account for inertia

//For Colour Range
#define MAX 11

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
void displayScreen (int spaceCount, int enterCount);		//displays the number of spaces and enters that have been used
void clearScreen();		//clears the screen on call
void displaySmiley();		//displays a smiley somewhere random
void expand (int size, int clear, int initX, int initY);		//expands the selected pixel to a square of lengths /size

//Basic Drive and Movement Functions
void rotate(int speed, int degrees);
void drive();
void BackUp();

//Inputs for Bumper, Sound, Light
void touchSensor(int direction, int &spaceCount, int &enterCount, int &consecEnter);
int listen();
int scanLight(range colourRange);

//Procedure Functions
void generateRange(int lightTarget, range colourRange);
int findKey(int key);

task main()
{
		//int lightTarget=35;
		int key=0; // space = 1, enter = 2, indicates whether it has approached the right target, it is 0 when it is still looking
		int keyTarget=0; // space = 1, enter = 2, indicates which thing it is targetting
		
		range greenRange;	//left (towards space)
	  range redRange;	//right (towards enter)
	  range blueRange;	//top (towards keyboard)
	  range yellowRange; //back (idk man, edge of the world)
	  range targetRange;
	  
		int zigged=1;
		
		int soundLevel;
		
		int light;
		
		generateRange(GREEN,greenRange);
	  generateRange(RED,redRange);
	  generateRange(BLUE,blueRange);
	  generateRange(YELLOW,yellowRange);
	  
		soundLevel=listen();
  
		if (soundLevel==1){
			keyTarget=1;
			generateRange(GREEN,targetRange);
		}
		else if(soundLevel==0){
			keyTarget=2;
			generateRange(RED,targetRange);
		}
		//HARDCODE~~~~~~~~~~~~~~~~~
		keyTarget=1;
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~
		nxtDisplayTextLine(3,"KEY:%d",keyTarget);
		
		while (key==0){
			key=findKey(keyTarget);	//keeps on driving until 
			wait10Msec(100);
			light=SensorValue[LIGHT];
		
		
		}
		clearScreen();
		nxtDisplayBigTextLine(2,"Found it");
		//the robot drives past the first line 
		drive();
		wait1Msec(1000);
		while (scanLight(targetRange)==0)	{
			drive();
			nxtDisplayBigTextLine(2,"ABOUT2ROTATE");
		}
		
		
		if (key==1){
			zigged=-1;	//first rotate will be to the right
			generateRange(GREEN,targetRange);
			rotate(DRIVESPEED,90*zigged);
		}
			
		else if (key==2){
			zigged=1;	//first rotate will be to the left
			generateRange(RED,targetRange);
			rotate(DRIVESPEED,90*zigged);
		}
	
		while (true) {
			clearScreen();
			nxtDisplayBigTextLine(2,"ROTATING");
			while (scanLight(targetRange)==0)
				drive();
		
			if (scanLight(targetRange)==1){ 	//when it does not sense the necessary colours
				wait1Msec(100);
				zigged=zigged*(-1);	//switches the direction of the rotation each time it hits a colour
			
			if(zigged==1)
				rotate(RSPEED,DEGREE);
			else if(zigged==-1)
				rotate(RSPEED,-DEGREE);
		}
			
		
		
	}

}


int findKey(int key){	//

	int position; //1 is left, 2 is right, 3 is top, 4 is bottom

	//int soundLevel;
	
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
	//nxtDisplayTextLine(1,"smallCOCK");
		//wait10Msec(100);
		clearScreen();
		nxtDisplayBigTextLine(1,"CANT FIND IT");
		
		rotate(RSPEED,180);
		return 0;
	}
	else if (position==2 && key==2){
		//drive towards enter
		//nxtDisplayTextLine(1,"BIGCOCK");
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
