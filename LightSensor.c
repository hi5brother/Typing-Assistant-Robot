//Christopher Ko
//March 11, 2014
//Light Sensor

/*
Colour 1 (Left Edge): Turns right towards keyboard and space bar
Colour 2 (Right Edge): Turns left towards keyboard and enter
Colour 3 (Front Edge): If loud, back up then go left to colour 1. If soft, back up then go right to colour 2.
Colour 4 (Back Edge): If loud, back up then go right to colour 1. If soft, back up then go left to colour 2.
*/

int LightSensor(int sound){
  int direction;
  int light; //current sensor light level
  
  SensorType[1]=sensorLightActive; //define the light sensor type on port S2
  nMotorPIDSpeedCtrl[LeftMotor]=mtrSpeedReg;
  nMotorPIDSpeedCtrl[RightMotor]=mtrSpeedReg;
  
  motor[1]=SPEED;
  motor[2]=SPEED;
  
  while(true){
      level=SensorValue[1]; //get the new light sensor value
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
              //Turn Left
              }
          else if (sound==0){
              //Backup a bit
              //Turn Right
              }
          }
      else if (light > COLOUR3 && light < COLOUR4){
          if (sound==1){
              //Backup a bit
              //Turn Right
              }
          else if (sound==0){
              //Backup a bit
              //Turn Left
              }
      }
    return direction;
}



