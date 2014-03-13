//Christopher Ko
//March 11, 2014
//Touch Sensor

/*
Rotate x degrees
*/

#define ROTATESCALE 2.06 //found from trial and error
#define EARLYSTOPFACTOR 0.30 //stop earlier to account for inertia
#define SPEED 20

void rotate(int speed, int degrees){
    int neededCount, actualCount;
    
    if (degrees>0){
        nMotorEncoder[RMOTOR]=0; //zero right encoder
        motor[1]=SPEED;
        motor[2]=-SPEED;
    }
    else{
        nMotorEncoder[LMOTOR]=0; //zero left encoder
        motor[1]=-SPEED;
        motor[2]=SPEED;
    }
    
    neededCount=abs(degrees)*ROTATIONSCALE;
    actualCount=0;
    
    while(actualCount<neededCount-(SPEED*EARLYSTOPFACTOR)){
        wait1MSec(5);
        
        if (degrees>0){
            actualCount=nMotorEncoder[RMOTOR];
        }
        else
            actualCount=nMotorEncoder[LMOTOR];
        }
    
    motor[RMOTOR]=0;
    motor[LMOTOR]=0;
    wait1Msec(200);
}
    