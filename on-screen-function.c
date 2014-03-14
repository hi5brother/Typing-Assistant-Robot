//Daniel Kao
//Mar 13, 2014
//On Screen Function v2
/*
No main function because these functions are included into the run file

*/

#define ROWS 7
#define COLS 7

#define MAXHEIGHT 64
#define MAXWIDTH 100

#define UPSIZE 4 //expands the pixel from 1 pixel to a square of 4x4 pixels

#define LEFT 30 //horizontal screen position at left edge of image
#define TOP 40 //vertical screen position at top edge of image

void displayScreen (int spaceCount, int enterCount); //displays the number of spaces and enters that have been used
void clearScreen;		//clears the screen on call
void displaySmiley;		//displays a smiley somewhere random

void expand (int size, int clear, int initX, int initY)	//expands the selected pixel to a square of lengths /size



void displayScreen (int spaceCount, int enterCount){		
	nxtDisplayTextLine (2, "Number of Spaces: %d", spaceCount);
	nxtDisplayTextLine (3, "Number of Enters: %d", enterCount);
	
}

void clearScreen{		//clears the screen on call
	int i;
	for (i=0; i<MAXLINES;i++){
		nxtDisplayClearTextLine(i);
	}
}

void displaySmiley{		//displays a smiley somewhere random
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
