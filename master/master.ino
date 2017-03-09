void setup(){
    Serial.print("in setup");
  Serial.begin(9600);
  setupDriveMotors();
  setupSonar();
  setupESC();

  pinMode(5, OUTPUT);
}


void loop(){
//  sonarPrintTest();
//driveForward(255);
//delay(100);
// turnTest();
//   driveForwardTest();
  goToFiringPosition(); 
  while(true){
    delay(100);  
  } 
}

void goToFiringPosition(){
  Serial.print("in gotofiringpos");
  // turnTest();
  turnUntilWallToRight();
  rightHandForwardWall(5);
  ninetyDegreeTurn();
  squishUpAgainstWall();
  driveForward(0);
  /*
  turn(-110, -1);
  delay(100);
  driveForward(0);
  rightHandForward(4000, 4, false);
  driveForward(0);
  */
}

