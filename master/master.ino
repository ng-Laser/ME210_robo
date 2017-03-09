void setup(){
  Serial.begin(9600);
  Serial.print("in setup");
  setupDriveMotors();
  setupSonar();
  //setupESC();
}


void loop(){
//  sonarPrintTest();
//driveForward(130);
//turn(110, 1.25); 
//turnTest();
//squishUpAgainstWall();
//delay(100);
// turnTest();
//sonarPrintTest();
// driveForwardTest();
  goToFiringPosition(); 
//  while(true){
//    delay(100);  
//  } 
}

void goToFiringPosition(){
  Serial.print("in gotofiringpos");
  // turnTest();
  turnUntilWallToRight();
  rightHandForwardWall(3);
  ninetyDegreeTurn();
//  squishUpAgainstWall();
  driveForward(0);
  /*
  turn(-110, -1);
  delay(100);
  driveForward(0);
  rightHandForward(4000, 4, false);
  driveForward(0);
  */
}

