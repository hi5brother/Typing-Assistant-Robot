//Christopher Ko
//March 11, 2014
//Touch Sensor

/*
Either Bumper: Record that a character has been input. Move away from the keyboard.
Two Consecutive Enter Commands: Terminate program.
Or two consecutive bumps or something
*/

void BackUp(int speed, int duration){
    int i, neededLoops;
    
    motor[1]=-SPEED;
    motor[2]=-SPEED;
    neededLoops=duration/500;
    
    for (i=0;i<neededLoops;i++){
        wait10MSec(20); //drive backwards for 200msecs
        PlayTone(1100,30); //play 1100Hz tone for 30msecs
        wait10MSec(30); //drive backwards while waiting for tone to finish
    }
    
    motor[1]=0;
    motor[2]=0;
}
