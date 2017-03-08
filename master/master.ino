void setup(){
  Serial.begin(9600);
  setupDriveMotors();
  setupSonar();
}


void loop(){  
  findStartPosition();
  
  while(true){
    delay(100);  
  }  
}


