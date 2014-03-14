//Christopher Ko
//March 11, 2014
//Touch Sensor

/*
Either Bumper: Record that a character has been input. Move away from the keyboard.
Two Consecutive Enter Commands: Terminate program.
*/

#define RBUMP 0
#define LBUMP 3
#define LIGHT 1
#define MICROPHONE 2
#define SPEED 25

//Pass the direction from LightSensor into TouchSensor and have it return spaceCount and enterCount values to be displayed on the screen
void touchSensor(int direction, int &spaceCount, int &enterCount, int &consecEnter){
    int spaceCount,enterCount;
    int leftBump, rightBump;
    int consecEnter=0;
    
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
            consecEnter++
            }
        }
        //Back away from the keyboard
        BackUp(SPEED,2000);
    }
}
