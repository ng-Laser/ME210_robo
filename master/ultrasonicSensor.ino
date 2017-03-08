#include "SonarSensor.h"

//pins
//These values can change as necessary
SonarSensor rightSonar = SonarSensor(2 , 3); // trigger , echo
SonarSensor frontSonar = SonarSensor(9 , 8); // trigger , echo
SonarSensor leftSonar = SonarSensor(12 , 10); // trigger , echo

//constants
const float FRONT_WALL_THRESHOLD = 6.0;       //Need to determine empirically
const float RIGHT_LEFT_SUM_THRESHOLD = 30.0;  //Need to determine empirically
const float RIGHT_THRESHOLD = 15.0;           //Need to determine empirically
const float LEFT_THRESHOLD = 15.0;            //Need to determine empirically
const unsigned int MAX_DIST = 23200;          //farthest range of ultrasonic sensor

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

void findStartPosition(){
  turn(110,-1);
  bool positionFound = false;
  while (positionFound == false) {
    float rightAverage = rightSonar.newAvgDistance(); // trigger , echo
    float frontAverage = frontSonar.newAvgDistance(); // trigger , echo
    float leftAverage  = leftSonar.newAvgDistance(); // trigger , echo
  
    Serial.print("right distance: ");
    Serial.print(rightAverage);
    Serial.print(" left distance: ");
    Serial.print(leftAverage);
    Serial.print(" front distance: ");
    Serial.println(frontAverage);

    if ((rightAverage >= RIGHT_THRESHOLD) && (frontAverage < 10) && (leftAverage >= LEFT_THRESHOLD)) {
        positionFound = true;
        driveForward(0);
        Serial.println("Start position found");
    }
  }
}

//void rightHandForward(int time);

void rightHandForward(int time){ // in ms 
  int timeInterval = 50;
  for(int i = 0 ; i < time*1.0/timeInterval; i++){
    //Serial.println("loop");
    float rightInches = rightSonar.getDistance();
    //Serial.println("rightdistancefound");
    float frontDistance = frontSonar.getDistance();
    //Serial.println("frontdistancefound");
    //Serial.print("front distance: ");
    //Serial.print(frontDistance);
    //Serial.print(" right distance: ");
    //Serial.println(rightInches);
    if (frontDistance > 5){
      //Serial.println("here1");
      if( rightInches > 6 ) {
        //Serial.println("right > 5");
        turn(137.5, .9); // 
      } else if (rightInches < 5) {
        //Serial.println("right < 3");
        turn(110, 1.25);  
      } else {
        //Serial.println("here2");
        driveForward(110);
      }
    } else {
      //Serial.println("here3");
      driveForward(0);
    }
    Serial.print("front distance: ");
    Serial.print(frontDistance);
    Serial.print(" right distance: ");
    Serial.println(rightInches);
    delay(timeInterval);
  }
}

