// motor one
int enMotorA = 5;
int  enMotorB = 6;

int driveAForward = 4 ;// 6;
int driveBForward = 7 ;// 6;

void setupDriveMotors()
{
  // set all the motor control pins to outputs
  pinMode(enMotorA, OUTPUT);
  pinMode(enMotorB, OUTPUT);
  pinMode(driveAForward, OUTPUT);
  pinMode(driveBForward, OUTPUT);
}

/*
 * Speed control for motorA
 * When speed == 0 the motor breaks
 * when speed > 0 turns in 'forward direction'
 * when speed < 0 turns in 'reverse direction'
*/
void motorAForward(int speed){
  if(speed == 0){ // stop 
    digitalWrite(enMotorA, LOW);       
    return;
  }
  if(speed > 0){ // running forward direction
    digitalWrite(driveAForward, HIGH);    
  }
  else{ // running in reverse
    digitalWrite(driveAForward, LOW);    
  }  
  analogWrite(enMotorA, abs(speed));
}

/*
 * Speed control for motorB
 * When speed == 0 the motor breaks
 * when speed > 0 turns in 'forward direction'
 * when speed < 0 turns in 'reverse direction'
*/
void motorBForward(int speed){
  if(speed == 0){ // stop 
    digitalWrite(enMotorB, LOW);       
    return;
  }
  if(speed > 0){ // running forward direction
    digitalWrite(driveBForward, HIGH);    
  }
  else{ // running in reverse
    digitalWrite(driveBForward, LOW);    
  }  
  analogWrite(enMotorB, abs(speed));

}

/*
 * This function wraps around the two motor controllers to go straight
 * When speed == 0 the motor breaks
 * when speed > 0 both of the motors turn in the 'forward direction'
 * when speed < 0 both motors turn in the 'reverse direction'
*/
void driveForward(int speed){
  motorAForward(speed);
  motorBForward(speed);
}

/*
 * This function wraps around the two motor controllers, allows for turning
 * Speed controlls the first motor, ratio allows relative motion 
 * When speed == 0 the motor breaks
 * when speed > 0 both of the motors turn in the 'forward direction'
 * when speed < 0 both motors turn in the 'reverse direction'
 * 
 * When ratio < 0 , motors turn in opposite directions
 * When ration 
*/
void turn(int speed, int ratio){
  motorAForward(speed);
  motorBForward(speed*ratio);
}


void driveForwardTest(){
  Serial.println("enter a speed between -255 to 255 for driving");
  int speed = _getUserInputInt();
  
  Serial.print("Driving ");
  Serial.println(speed);
  driveForward(speed);
  //driveForward(-255);
  delay(100);  
}

void turnTest(){
  Serial.println("enter a speed between -255 to 255 for turn");
  int speed = _getUserInputInt();

  Serial.println("enter a ratio between -1 , 1 for turn");
  while(!Serial.available()){
      delay(100);
  }
  float ratio = Serial.parseFloat();
  
  Serial.print("Turn ");  Serial.print(speed);
  Serial.print(" ");  Serial.println(ratio);

  turn(speed, ratio);
  delay(100);  
}

int _getUserInputInt(){
  while(!Serial.available()){
      delay(100);
  }
  return Serial.parseInt();  
}
