
/* This is a sample Program
   Use File->Load C Prog to
   load a different Program
*/

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

    
    nxtDisplayTextLine(3,"HI");
}

