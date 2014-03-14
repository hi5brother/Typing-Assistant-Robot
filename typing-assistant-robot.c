//Daniel Kao and Christopher Ko
//APSC 142: Typing Assistant Robot
//March 2014

#include "sound-function.c"
#include "on-screen-function.c"
#include "TouchSensor.c"
#include "LightSensor.c"
#include "BackUp.c"
#include "Rotate.c"
#include "line-follow.c"

#define RMOTOR 1
#define LMOTOR 3
#define RBUMP 0
#define LBUMP 3
#define LIGHT 1
#define MICROPHONE 2

/* Other Definitions
#define COLOUR1 25
#define COLOUR2 50
#define COLOUR3 75
#define COLOUR4 100

#define SPEED 50
*/

task main()
{
    int sound,direction;
    int spaceCount, enterCount, consecEnter;
    //Turn on speed regulation for accurate tracking
    nMotorPIDSpeedCtrl[RMOTOR]=mtrSpeedReg;
    nMotorPIDSpeedCtrl[LMOTOR]=mtrSpeedReg;
    
    //Turn on touch sensors for bumpers
    SensorType[RBUMP]=sensorTouch; //right
    SensorType[LBUMP]=sensorTouch; //left
    
    //Define the light sensor type on port S2
    SensorType[LIGHT]=sensorLightActive;
    
    //Sound
    SensorType[MICROPHONE]=sensorSoundDBA;

    sound=listen();
    direction=lightSensor(sound);
    touchSensor(direction,spaceCount,enterCount,consecEnter);
    displayScreen(spaceCount,enterCount);
    clearScreen;
    displaySmiley;
    
}

