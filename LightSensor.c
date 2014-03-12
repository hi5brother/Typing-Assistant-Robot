//Christopher Ko
//March 11, 2014
//Light Sensor

/*
Colour 1 (Left Edge): Turns right towards keyboard and space bar
Colour 2 (Right Edge): Turns left towards keyboard and enter
Colour 3 (Front Edge): If loud, back up then go left to colour 1. If soft, back up then go right to colour 2.
Colour 4 (Back Edge): If loud, back up then go right to colour 1. If soft, back up then go left to colour 2.

*/


#define COLOUR1 25
#define COLOUR2 50
#define COLOUR3 75
#define COLOUR4 100
#define SPEED 50


int LightSensor(int);

task main(){
}


int LightSensor(int sound){
  int LeftMotor, RightMotor;
  int direction;
  
  nMotorPIDSpeedCtrl[LeftMotor]=mtrSpeedReg;
  nMotorPIDSpeedCtrl[RightMotor]=mtrSpeedReg;
  
  while(true){
      motor[LeftMotor]=SPEED;
      motor[RightMotor]=SPEED;
      
      if (SensorValue(lightSensor) < COLOUR1){
          //Turn right
          direction=0;
          break;
          }
      else if  (SensorValue(lightSensor) > COLOUR1 && SensorValue(lightSensor) < COLOUR2){
          //Turn Left
          direction=1;
          break;
          }
      else if (SensorValue(lightSensor) > COLOUR2 && SensorValue(lightSensor) < COLOUR3){
          if (sound==1){
              //Backup a bit
              //Turn Left
              }
          else if (sound==0){
              //Backup a bit
              //Turn Right
              }
          }
      else if (SensorValuelightSensor) > COLOUR3 && SensorValue(lightSensor) < COLOUR4){
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



