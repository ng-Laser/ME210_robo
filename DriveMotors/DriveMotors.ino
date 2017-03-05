#include <Servo.h> // for ESC

// connect motor controller pins to Arduino digital pins
// in1 , in2 into normal digital output pins
// enable in digital write
// motor one
int enA = 6;
int in1 = 7;
int in2 = 8;
// motor two
int enB = 11;
int in3 = 12;
int in4 = 13;

#define SHOOTER_PWM 5
Servo shooterESC;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
//  pinMode(, OUTPUT);
  shooterESC.attach(SHOOTER_PWM);
//     shooterMotor(200);
}

/*
 * Speed control for motorA
 * When speed == 0 the motor breaks
 * when speed > 0 turns in 'forward direction'
 * when speed < 0 turns in 'reverse direction'
*/
void motorAForward(int speed){
  if(speed == 0){ // stop 
    digitalWrite(in1, LOW); // turn off motor A  
    digitalWrite(in2, LOW);  
    return;
  }
  if(speed > 0){ // running forward direction
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);    
  }
  else{ // running in reverse
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);    
  }  
  analogWrite(enA, abs(speed)); // determine speed 
}

/*
 * Speed control for motorB
 * When speed == 0 the motor breaks
 * when speed > 0 turns in 'forward direction'
 * when speed < 0 turns in 'reverse direction'
*/
void motorBForward(int speed){
  if(speed == 0){
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);  
    return;
  }
  if(speed > 0){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);    
  }
  else{
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
  }
  analogWrite(enB, abs(speed));
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

void shooterMotor(int speed){
  analogWrite(SHOOTER_PWM, abs(speed)); // determine speed 
  //myservo.writeMicroseconds(1000);
}

void loop()
{
  // shooterMotor(200);
  shooterESC.writeMicroseconds(1500);
  driveForward(200);
  delay(1000);
  driveForward(0);
  delay(1000);
  driveForward(-200);
  delay(1000);
  driveForward(0);
  delay(1000);

}

