#include "SonarSensor.h"

//pins
//These values can change as necessary
SonarSensor rightSonar = SonarSensor(2 , 3); // trigger , echo
SonarSensor frontSonar = SonarSensor(9 , 8); // trigger , echo
SonarSensor leftSonar = SonarSensor(12 , 13); // trigger , echo

//constants
const float FRONT_WALL_THRESHOLD = 6.0;       //Need to determine empirically
const float RIGHT_LEFT_SUM_THRESHOLD = 30.0;  //Need to determine empirically
const float FAR_THRESHOLD = 15.0;           //Need to determine empirically
const unsigned int MAX_DIST = 23200;          //farthest range of ultrasonic sensor
const float TURNING_THRESHOLD = 4.7;

void setupSonar() {
  setupPins();
}

void setupPins(){
  rightSonar.setUp(); // trigger , echo
  frontSonar.setUp(); // trigger , echo
  leftSonar.setUp(); // trigger , echo
}

void sonarPrintTest(){
    float rightAverage = rightSonar.newAvgDistance(); // trigger , echo
    float frontAverage =  frontSonar.newAvgDistance(); // trigger , echo
    float leftAverage = leftSonar.newAvgDistance(); // trigger , echo    
    Serial.print("right distance: ");
    Serial.print(rightAverage);
    Serial.print(" left distance: ");
    Serial.print(leftAverage);
    Serial.print(" front distance: ");
    Serial.println(frontAverage);  
}

void rightHandForward(int time, float threshold, bool breakForFrontWall ){ // in ms 
  int timeInterval = 50;

  float rightInches = rightSonar.newAvgDistance();
  float frontDistance = frontSonar.newAvgDistance();
    Serial.print("front distance: ");
    Serial.print(frontDistance);
    Serial.print(" right distance: ");
    Serial.println(rightInches);

  
  for(int i = 0 ; i < time*1.0/timeInterval; i++){
    //Serial.println("loop");
    float rightInches = rightSonar.newAvgDistance();
    float frontDistance = frontSonar.newAvgDistance();
    Serial.print("front distance: ");
    Serial.print(frontDistance);
    Serial.print(" right distance: ");
    Serial.println(rightInches);
    if(breakForFrontWall && frontDistance < 5) break;
    
    if( rightInches > threshold ) {
      turn(125, .9); // 
    } else if (rightInches < threshold *.8) {
      turn(110, 1.25);  
    } else {
      driveForward(110);
    }    
    delay(timeInterval);
  }
}

void rightHandForwardWall(float threshold){ // in ms 
  int timeInterval = 50;

  float rightInches = rightSonar.newAvgDistance();
  float frontDistance = frontSonar.newAvgDistance();
    Serial.print("front distance: ");
    Serial.print(frontDistance);
    Serial.print(" right distance: ");
    Serial.println(rightInches);

  
    while(frontDistance > threshold && frontDistance < 500){
      //Serial.println("loop");
      rightInches = rightSonar.newAvgDistance();
      frontDistance = frontSonar.newAvgDistance();
      Serial.print("move right wall front distance: ");
      Serial.print(frontDistance);
      Serial.print(" right distance: ");
      Serial.println(rightInches);
      
      if( rightInches > threshold ) {
        turn(125, .9); // 
      } else if (rightInches < threshold *.8) {
        turn(110, 1.25);  
      } else {
        driveForward(110);
      }    
      delay(timeInterval);
    }
}

void squishUpAgainstWall(){  
  for(int i = 0 ; i < 30 ; ++i){
    turn(150, .85);
    
    frontSonar.newAvgDistance(); 
    frontSonar.newAvgDistance();
    delay(800);
    
    if(frontSonar.newAvgDistance() < 12){
      turn(-180, -.5);    
      delay(100);
    }
  }
}

void turnUntilWallToRight(){
  turn(127,-1);
  float rightAverage , frontAverage , leftAverage;
  do {
    rightAverage = rightSonar.newAvgDistance(); // trigger , echo
    frontAverage = frontSonar.newAvgDistance(); // trigger , echo
    leftAverage  = leftSonar.newAvgDistance(); // trigger , echo    
    Serial.print("right distance: ");  Serial.println(rightAverage);
    Serial.print(" left distance: ");  Serial.println(leftAverage);
    Serial.print(" front distance: "); Serial.println(frontAverage);  
  } while (!((frontAverage >= 12) && (rightAverage < 10) && (leftAverage >= FAR_THRESHOLD)));
  
  driveForward(0);
  if(frontAverage > 13){
    turn(-127,-1);
    delay(150);
    driveForward(0);
  }
  Serial.println("Start position found");
}


void ninetyDegreeTurn(){
  turn(-130,-.8);
  delay(1000);
  turn(-110,-1);
  float rightAverage = rightSonar.newAvgDistance();
  float frontAverage = frontSonar.newAvgDistance();
  Serial.print("initial right Average: ");
  Serial.println(rightAverage);
  Serial.print("initial front Average: ");
  Serial.println(frontAverage);
  while((rightAverage > 4.7)){// || (frontAverage < 15)) {
    rightAverage = rightSonar.newAvgDistance();
    frontAverage = frontSonar.newAvgDistance();
    Serial.print("right Average INSIDE TURN: ");
    Serial.println(rightAverage);
    Serial.print("front Average INSIDE TURN: ");
    Serial.println(frontAverage);
  }
  Serial.print("out of while loop");
  driveForward(0);
}


