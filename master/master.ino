void setup(){
  Serial.begin(9600);
  setupDriveMotors();
  setupSonar();
}

void alignToFirstSpot(){
  turn(-110, -1);
  alignWithWall();
  while(true){
    delay(100);  
  }  
}

void loop(){
 alignToFirstSpot();

  driveForward(0);
  while(true){
    delay(100);  
  }  
}


