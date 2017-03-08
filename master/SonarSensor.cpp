#include "SonarSensor.h"

SonarSensor::SonarSensor(int triggerPin_in, int echoPin_in)
{
	triggerPin = triggerPin_in;
	echoPin = echoPin_in;
}

void SonarSensor::setUp(){
	pinMode(triggerPin, OUTPUT);
	digitalWrite(triggerPin, LOW);
	pinMode(echoPin, INPUT);
	prevVal = this->getDistance();
	secondPrevVal =prevVal;
}

float SonarSensor::getDistance(){
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

float SonarSensor::newAvgDistance(){
	float currentDistance = getDistance();
	float avg = (currentDistance + prevVal + secondPrevVal )/3.0;
	prevVal = currentDistance;
	secondPrevVal = prevVal;
	return avg; 

}