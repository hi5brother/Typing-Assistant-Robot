//Christopher Ko
//March 11, 2014
//Touch Sensor

/*
Either Bumper: Record that a character has been input. Move away from the keyboard.
Two Consecutive Enter Commands: Terminate program.
Or two consecutive bumps or something
*/

//Pass the direction from LightSensor into TouchSensor and have it return spaceCount and enterCount values to be displayed on the screen
void TouchSensor(int direction, int &spaceCount, int &enterCount){
    int spaceCount,enterCount;
    int leftBump, rightBump;
    
    //Initialize Sensors
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
}
    //Figure out how to time for two consecutive bumps or how to count two consec enters