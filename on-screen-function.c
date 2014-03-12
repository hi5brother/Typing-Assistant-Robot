//Daniel Kao
//Mar 11, 2014
//On Screen Function
/*


*/


#define ROWS 7	//roughly proportional to full screen
#define COLS 10

#define MAXHEIGHT 64
#define MAXWIDTH 100

#define UPSIZE 4

#define LEFT 30 //horizontal screen position at left edge of image
#define TOP 40 //vertical screen position at top edge of image

void displayScreen (int, int);
void displaySmiley;
void clearScreen;
void expand (int, int, int, int);



task main (){
	int spaceCount=5;
	int enterCount=3;
	
}

void displayScreen (int spaceCount, int enterCount){
	nxtDisplayTextLine (2, "Number of Spaces: %d", spaceCount);
	nxtDisplayTextLine (3, "Number of Enters: %d", enterCount);
	
}

void clearScreen{
	int i;
	for (i=0; i<MAXLINES;i++){
		nxtDisplayClearTextLine(i);
	}
}

void displaySmiley{
	int i, j; //row and column
	int x, y; //screen x and y coordinates
	int a,b; //start coordinates of the smiley	
	int rows, cols;
	int upsize;
	byte image[ROWS][COLS]=
			{	{1,1,1,0,0,0,0,1,1,1},
				{1,1,0,0,0,0,0,0,1,1},
				{1,1,0,1,0,0,1,0,1,1},
				{1,1,0,0,0,0,0,0,1,1},
				{1,1,0,1,1,1,1,0,1,1},
				{1,1,0,0,1,1,0,0,1,1},
				{1,1,1,0,0,0,0,1,1,1},
			};
	a=random(MAXWIDTH-(cols*upsize));
	b=random(MAXHEIGHT-(rows*upsize))+(rows*upsize);
	
	for(i=0; i<=rows-1; i++)
	{
		for(j=0; j<=cols-1; j++)
		{
			x = a+j*upsize; //set x screen position according to the column value
			y = b-i*upsize; //set y screen position according to the row value
			if(image[i][j] == 1)
			{
				expand (upsize,1,x,y);
			}
			else if(image[i][j] == 0)
			{
				expand (upsize,0,x,y);
			}
			
		}
		wait10Msec(20);
	}
	wait10Msec(200);//delay end of program so we can image on the screen
}
			
void expand (int size, int clear, int initX, int initY)
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
