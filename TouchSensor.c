//Christopher Ko
//March 11, 2014
//Touch Sensor

/*
Either Bumper: Record that a character has been input. Move away from the keyboard.
Two Consecutive Enter Commands: Terminate program.
Or two consecutive bumps or something
*/

void BackUp(int, int);
void TouchSensor(int, int, int);

task main(){
}

void BackUp(int speed, int duration){ //Make this a separate function? Since it's needed in LightSensor as well. Also make one for rotating to be used in LightSensor
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

//Pass the direction from LightSensor into TouchSensor and have it return spaceCount and enterCount values to be displayed on the screen
void TouchSensor(int direction, int &spaceCount, int &enterCount){
    int spaceCount,enterCount;
    int leftBump, rightBump;

    //Initialize sensors
    SensorType[0]=sensorTouch;
    SensorType[3]=sensorTouch;
    nMotorPIDSpeedCtrl[1]=mtrSpeedReg;
    nMotorPIDSpeedCtrl[2]=mtrSpeedReg;
    
    leftBump=SensorValue[0];
    rightBump=SensorValue[3];
    
    if (leftBump==1 || rightBump==1){
        if (direction==0){
            spaceCount+=1;
            }
        else if (direction==1){
            enterCount+=1;
            }
        }
        //Back away from the keyboard
        BackUp(SPEED,2000);
        
    }
    
    //Figure out how to time for two consecutive bumps or how to count two consec enters