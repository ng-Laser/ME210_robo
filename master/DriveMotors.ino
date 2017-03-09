// motor one
int enmotorLeft = 5;
int enmotorRight = 11;

int driveAForward = 4 ;// 6;
int driveBForward = 7 ;// 6;

void setupDriveMotors()
{
  // set all the motor control pins to outputs
  pinMode(enmotorLeft, OUTPUT);
  pinMode(enmotorRight, OUTPUT);
  pinMode(driveAForward, OUTPUT);
  pinMode(driveBForward, OUTPUT);
}

/*
 * mySpeed control for motorLeft
 * When mySpeed == 0 the motor breaks
 * when mySpeed > 0 turns in 'forward direction'
 * when mySpeed < 0 turns in 'reverse direction'
*/
void motorLeftForward(int mySpeed){
  if(mySpeed == 0){ // stop 
    analogWrite(enmotorLeft, 0);       
    return;
  }
  if(mySpeed > 0){ // running forward direction
    digitalWrite(driveAForward, HIGH);    
  }
  else{ // running in reverse
    digitalWrite(driveAForward, LOW);    
  }  
  analogWrite(enmotorLeft, abs(mySpeed));
}

/*
 * mySpeed control for motorRight
 * When mySpeed == 0 the motor breaks
 * when mySpeed > 0 turns in 'forward direction'
 * when mySpeed < 0 turns in 'reverse direction'
*/
void motorRightForward(int mySpeed){
  if(mySpeed == 0){ // stop 
    analogWrite(enmotorRight, LOW);       
    return;
  }
  if(mySpeed > 0){ // running forward direction
    digitalWrite(driveBForward, HIGH);    
  }
  else{ // running in reverse
    digitalWrite(driveBForward, LOW);    
  }  
  analogWrite(enmotorRight, abs(mySpeed));

}

/*
 * This function wraps around the two motor controllers to go straight
 * When mySpeed == 0 the motor breaks
 * when mySpeed > 0 both of the motors turn in the 'forward direction'
 * when mySpeed < 0 both motors turn in the 'reverse direction'
*/
void driveForward(int mySpeed){
  motorLeftForward(mySpeed);
  motorRightForward(mySpeed);
}

/*
 * This function wraps around the two motor controllers, allows for turning
 * mySpeed controlls the first motor, ratio allows relative motion 
 * When mySpeed == 0 the motor breaks
 * when mySpeed > 0 both of the motors turn in the 'forward direction'
 * when mySpeed < 0 both motors turn in the 'reverse direction'
 * 
 * When ratio < 0 , motors turn in opposite directions
 * When 0 < ration < 1 , right motor turns slower 
*/
void turn(int mySpeed, float ratio){
  motorLeftForward(mySpeed);
  motorRightForward(mySpeed*ratio);
}

void driveForwardTest(){
  Serial.println("enter a mySpeed between -255 to 255 for driving");
  int mySpeed = _getUserInputInt();
  Serial.print("Driving ");
  Serial.println(mySpeed);
  driveForward(mySpeed);
}

void turnTest(){
  Serial.println("enter a mySpeed between -255 to 255 for turn");
  int mySpeed = _getUserInputInt();

  Serial.println("enter a ratio between -1 , 1 for turn");
  while(!Serial.available()){
      delay(100);
  }
  float ratio = Serial.parseFloat();
  
  Serial.print("Turn ");  Serial.print(mySpeed);
  Serial.print(" ");  Serial.println(ratio);

  turn(mySpeed, ratio);
  delay(100);  
}

int _getUserInputInt(){
  while(!Serial.available()){
      delay(100);
  }
  int returnInt = Serial.parseInt();
  Serial.flush();
  return returnInt;  
}

