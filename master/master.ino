void setup(){
  Serial.begin(9600);
  setupDriveMotors();
  setupSonar();
}

void loop(){
  turn(110, -1);

  alignWithWall();
  while(true){
    delay(100);  
  }
}
