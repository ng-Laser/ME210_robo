#include <Servo.h> // for ESC

// motor one
int in1 = 6;
int in2 = 5; // pin 9, 10 pwm didn't work 
// motor two
int in3 = 11;
int in4 = 12;

#define SHOOTER_PWM 9
Servo shooterESC;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  shooterESC.attach(SHOOTER_PWM);

  Serial.begin(9600);
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
    // digitalWrite(in1, HIGH);
    analogWrite(in1, abs(speed)); // determine speed 
    digitalWrite(in2, LOW);    
  }
  else{ // running in reverse
    Serial.print("in negative!\nwriting ");
    digitalWrite(in1, LOW);
    analogWrite(in2, abs(speed)); // determine speed 
    Serial.println(abs(speed));
  }  

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
    analogWrite(in3, abs(speed));
    // digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);    
  }
  else{
    analogWrite(in4, abs(speed));
    digitalWrite(in3, LOW);
    //digitalWrite(in4, HIGH); 
  }

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
  shooterESC.writeMicroseconds(1000);
}

void loop()
{
  // demo
  Serial.println("enter a speed between -255 to 255 for driving");
  while(!Serial.available()){
      delay(100);
  }
  int speed = Serial.parseInt();
  Serial.print("Driving ");
  Serial.println(speed);
  driveForward(speed);
  //driveForward(-255);
  delay(100);
/*
  driveForward(200);
  delay(1000);
  driveForward(0);
  delay(1000);
  driveForward(-200);
  delay(1000);
  driveForward(0);
  delay(1000);*/
}


