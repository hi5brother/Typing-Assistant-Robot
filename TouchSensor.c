//Christopher Ko
//March 11, 2014
//Touch Sensor

/*
Either Bumper: Record that a character has been input. Move away from the keyboard.
Two Consecutive Enter Commands: Terminate program.
Or two consecutive bumps or something
*/

void TouchSensor(int);

task main(){
}

void TouchSensor(int direction){
    int spaceCount,enterCount;

    SensorType[0]=sensorTouch;
    SensorType[3]=sensorTouch;
    
    if (SensorValue(touchSensor)==1 || SensorValue(touchSensor)==1){
        if (direction==0){
            spaceCount+=1;
            }
        else if (direction==1){
            enterCount+=1;
            }
        }
        
        //Back away from the keyboard
    }
    
    //Figure out how to time for two consecutive bumps or how to count two consec enters