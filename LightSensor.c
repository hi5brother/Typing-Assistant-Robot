//Christopher Ko
//March 11, 2014
//Light Sensor

/*
Colour 1 (Left Edge): Turns right towards keyboard and space bar
Colour 2 (Right Edge): Turns left towards keyboard and enter
Colour 3 (Front Edge): If loud, back up then go left to colour 1. If soft, back up then go right to colour 2.
Colour 4 (Back Edge): If loud, back up then go right to colour 1. If soft, back up then go left to colour 2.
*/

#define RMOTOR 1
#define LMOTOR 3
#define LIGHT 1
#define SPEED 50

int lightSensor(int sound){
  int direction;
  int light; //current sensor light level
  
  motor[RMOTOR]=SPEED;
  motor[LMOTOR]=SPEED;
  
  while(true){


      light=SensorValue[LIGHT]; //get the new light sensor value
      if (light < COLOUR1){
          //Turn right
          direction=0;
          break;
          }
      else if  (light > COLOUR1 && light < COLOUR2){
          //Turn Left
          direction=1;
          break;
          }
      else if (light > COLOUR2 && light < COLOUR3){
          if (sound==1){
              //Backup a bit
              BackUp();
              //Turn Left
              }
          else if (sound==0){
              //Backup a bit
              BackUp();
              //Turn Right
              }
          }
      else if (light > COLOUR3 && light < COLOUR4){
          if (sound==1){
              //Backup a bit
              BackUp();
              //Turn Right
              }
          else if (sound==0){
              //Backup a bit
              BackUp();
              //Turn Left
              }
      }
    return direction;
}



