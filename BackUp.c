//Christopher Ko
//March 11, 2014
//Touch Sensor

/*
Back up for 200 msecs while playing 1100Hz tone for 30 msecs. Then motors stop.
*/

#define RMOTOR 1
#define LMOTOR 3
#define SPEED 25
#define DURATION 2000
#define TONE 1100

void BackUp(){
    int i, neededLoops;
    
    motor[RMOTOR]=-SPEED;
    motor[LMOTOR]=-SPEED;
    neededLoops=DURATION/500;
    
    for (i=0;i<neededLoops;i++){
        wait10MSec(20); //drive backwards for 200msecs
        PlayTone(TONE,30); //play 1100Hz tone for 30msecs
        wait10MSec(30); //drive backwards while waiting for tone to finish
    }
    
    motor[RMOTOR]=0;
    motor[LMOTOR]=0;
}
