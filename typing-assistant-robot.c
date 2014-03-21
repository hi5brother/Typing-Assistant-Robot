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
#define LBUMP 2

#define LIGHT 0

#define MICROPHONE 2

#define BULB 3

//Define light thresholds for the different boundaries

#define COLOUR1 25
#define COLOUR2 50
#define COLOUR3 75
#define COLOUR4 100

#define GREEN 35
#define RED 60
#define BLUE 20
#define YELLOW 30

//Define speeds
#define DRIVESPEED 5
#define RSPEED 5
#define BACKSPEED 5
#define DEGREE 50

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
#define SOUNDTHRESH 65
#define AMBIENT 25

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

//Drive and Movement Functions
void rotate(int speed, int degrees);
void drive();
void BackUp();

//Inputs for Bumper, Sound, Light
void touchSensor(int direction, int &spaceCount, int &enterCount, int &consecEnter);
int listen();
int scanLight(range colourRange);

void generateRange(int lightTarget, range colourRange);

task main()
{
		int lightTarget=35;
		
		range greenRange;	//left (towards space)
	  range redRange;	//right (towards enter)
	  range blueRange;	//top (towards keyboard)
	  range yellowRange; //back (idk man, edge of the world)
	  
	  int position; //1 is left, 2 is right, 3 is top, 4 is bottom
	  
		int soundLevel;
		int key; // space = 1, enter = 2
    
		sensorInitialize();
		
		generateRange(GREEN,greenRange);
	  generateRange(RED,redRange);
	  generateRange(BLUE,blueRange);
	  generateRange(YELLOW,yellowRange);
		
    soundLevel=listen();
    
    if (soundLevel==1)
    	key=1;
   	else if(soundLevel==0)
   		key=2;
    nxtDisplayTextLine(2,"%d",key);
    
    while (scanLight(greenRange)!=0 || scanLight(redRange)!=0 || scanLight(blueRange)!=0||scanLight(yellowRange)!=0){
    	drive();	//keeps on driving until it hits a colour
  	}
   	//finds the position of the robot depending on what colour it senses first
    	
  	if (scanLight(greenRange)==1)
  		position=1;	//hit left
  	else if (scanLight(redRange)==1)
  		position=2;	//hit right
  	else if (scanLight(blueRange)==1)
  		position=3;	//hit top
    else if (scanLight(yellowRange)==1)
  		position=4; //hit bottom
  	
  	if (position==1 && key==1){
  		//drive towards space
  		nxtDisplayTextLine(1,"BIGCOCK");
  		wait1Msec(100);
  	}
  	else if (position==1 && key==2){
  		//turn around	
  		rotate(RSPEED,180);
  	}
  	else if (position==2 && key==1){
  		//turn around
  	//nxtDisplayTextLine(1,"smallCOCK");
  		//wait10Msec(100);
  		rotate(RSPEED,180);
  	}
  	else if (position==2 && key==2){
  		//drive towards enter
  		nxtDisplayTextLine(1,"BIGCOCK");
  		wait1Msec(100);

  	}
    else if (position==3 && key==1){
  		//turn left
    	rotate(RSPEED,-DEGREE);
  	} 
  	else if (position==3 && key==2){
  		//turn right
  		rotate(RSPEED,DEGREE);
  	} 
  	else if (position==4 && key==1){
  		//turn right
  		rotate(RSPEED,DEGREE);
  	} 
  	else if (position==4 && key==2){
  		//turn left
  		rotate(RSPEED,-DEGREE);
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
	return 1;
}


void drive ()
{
	motor[RMOTOR]=DRIVESPEED;
	motor[LMOTOR]=DRIVESPEED;
}

void rotate (int speed, int degrees)
{
	int neededCount, actualCount;

	if (degrees>0)
	{
		nMotorEncoder[RMOTOR]=0; //zero right encoder
		motor[RMOTOR]=speed;
		motor[LMOTOR]=-speed;
	}
	else
	{
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
