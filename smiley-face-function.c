

/*
	lab5_draw.c

	Draws an image array on the LCD display
*/
#define ROWS 7	//roughly proportional to full screen
#define COLS 10



#define LEFT 30  //horizontal screen position at left edge of image
#define TOP 40  //vertical screen position at top edge of image

#define UPSIZE 4
void expand (int, int, int, int);

task main()
{
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
	
	a=random(MAXWIDTH-(COLS*UPSIZE));
	b=random(MAXHEIGHT-(ROWS*UPSIZE))+(ROWS*UPSIZE);
	
	for(i=0; i<=ROWS-1; i++)
	{
		for(j=0; j<=COLS-1; j++)
		{
			x = a+j*UPSIZE; //set x screen position according to the column value
			y = b-i*UPSIZE; //set y screen position according to the row value
			if(image[i][j] == 1)
			{
				expand (UPSIZE,1,x,y);
			}
			else if(image[i][j] == 0)
			{
				expand (UPSIZE,0,x,y);
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