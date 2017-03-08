#include "HC_SR04.h"

HC_SR04::HC_SR04(int triggerPin_in, int echoPin_in)
{
	triggerPin = triggerPin_in;
	echoPin = echoPin_in;
}

void setUp(){
	pinMode(triggerPin, OUTPUT);
	digitalWrite(triggerPin, LOW);
	pinMode(echoPin, INPUT);
	prevVal = getDistance();
	secondPrevVal = getDistance();
}

float HC_SR04::getDistance(){
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  while ( digitalRead(echoPin) == 0 );
  t1 = micros();
  while ( digitalRead(echoPin) == 1);
  t2 = micros();
  pulse_width = t2 - t1;
  inches = pulse_width / 148.0;
  return inches;
 }
}

float HC_SR04::newAvgDistance(){
	return (getDistance()+ 	prevVal + secondPrevVal )/3.0;

}