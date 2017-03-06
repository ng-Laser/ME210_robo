 #include <Timers.h> // for sonar

// Sonar sensor Pins/variables
const int TRIG_PIN = 3;
const int ECHO_PIN = 2;
volatile float previous = 100.0;
volatile float second_previous = 101.0;
volatile float running_average = 100;
volatile float minimum_average = 1000;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;
const float THRESHOLD = 0.2;

void determineMinimum(void);
void turnToMinimum(void);
float getDistance(void);

// end sonar sensor stuff 


/* Start Drive Motors stuff */
// motor one
int in1 = 10 ;// 6;
int in2 = 5; // pin 9, 10 pwm didn't work 
// motor two
int in3 = 11;
int in4 = 6;// 10;

/* End drive Motors stuff*/
void setup() {

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(9600);
  TMRArd_InitTimer(0,5000);

  /* Start drive motor stuff */
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  turn(-70, -1);
  /* End drive motors stuff */
}

void loop() {
  if ((unsigned char)TMRArd_IsTimerExpired(0)){
    // driveForward(0);
    // Serial.println("timer expired");
    //delay(1000);
    turnToMinimum();
  } else {
    determineMinimum();
  }
}

void determineMinimum(){
  float inches = getDistance();
  running_average = (second_previous+previous+inches)/3;
  if (running_average < minimum_average) minimum_average = running_average;
  second_previous = previous;
  previous = inches;
  Serial.print("average: ");
  Serial.print(running_average);
  Serial.print("minimum: ");
  Serial.print(minimum_average);
     
}

void turnToMinimum(){
  float inches = getDistance();
  running_average = (second_previous+previous+inches)/3;
  if (running_average < minimum_average + THRESHOLD) {
    //Stop motors
    Serial.println("Stop");
    driveForward(0);
  }
  Serial.print("average: ");
  Serial.print(running_average);
  Serial.print("minimum: ");
  Serial.print(minimum_average);
     
  second_previous = previous;
  previous = inches;
}

float getDistance(){
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  while ( digitalRead(ECHO_PIN) == 0 );
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;
  inches = pulse_width / 148.0;
  return inches; 
}


/* Start Drive motor stuff */

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
/* End Drive motor stuff */
