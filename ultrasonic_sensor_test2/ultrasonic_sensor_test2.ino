/**
 * HC-SR04 Demo
 * Demonstration of the HC-SR04 Ultrasonic Sensor
 * Date: August 3, 2016
 * 
 * Description:
 *  Connect the ultrasonic sensor to the Arduino as per the
 *  hardware connections below. Run the sketch and open a serial
 *  monitor. The distance read from the sensor will be displayed
 *  in centimeters and inches.
 * 
 * Hardware Connections:
 *  Arduino | HC-SR04 
 *  -------------------
 *    5V    |   VCC     
 *    7     |   Trig     
 *    8     |   Echo     
 *    GND   |   GND
 *  
 * License:
 *  Public Domain
 */

 #include <Timers.h>



// Pins
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

void setup() {

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(9600);
  TMRArd_InitTimer(0,5000);
}

void loop() {
  if (TMRArd_IsTimerExpired(0)){
    turnToMinimum();
  } else {
    determineMinimum();
  }
  
/*
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  //Serial.println("here");
  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );
  //Serial.println("here2");
  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;
  //Serial.print("here3");
  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  inches = pulse_width / 148.0;

  // Print out results
  if ( pulse_width > MAX_DIST ) {
    Serial.println("Out of range");
  } else {
    //Serial.print(cm);
    //Serial.print(" cm \t");
    running_average = (second_previous+previous+inches)/3;
    if (running_average < minimum_average) minimum_average = running_average;
    Serial.print(running_average);
    Serial.println(" average in");
    Serial.print(inches);
    Serial.println(" in");
    second_previous = previous;
    previous = inches;    
  }
  
  // Wait at least 60ms before next measurement
  delay(1000);*/
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

